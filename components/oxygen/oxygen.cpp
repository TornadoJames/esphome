#include "oxygen.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace oxygen_sensor {

static const char *const TAG = "oxygen_sensor";

// Internal helper variables
static float oxygen_key = 20.9f / 120.0f;  // Default fallback
static float last_oxygen_value = 0.0f;
static float voltage = 0.0f;       // Calibration voltage
static float millivoltage = 0.0f;   // Calibration millivolt reading

// -----------------------------
// OxygensSensor class
// -----------------------------
void OxygenSensor::update() { 
  this->read_oxygen_data_();
}

void OxygenSensor::read_oxygen_data_() {
  uint8_t result[3] = {0};
  if (this->read_bytes(OXYGEN_DATA_REGISTER, result, 3)) {
    float oxygen = (result[0] + (result[1] / 10.0f) + (result[2] / 100.0f)) / 5.3f;
    if (oxygen < 25.0f) {
      this->publish_state(oxygen);
      last_oxygen_value = oxygen;
    } else {
      this->publish_state(-1.0f);  // Invalid reading
      ESP_LOGW(TAG, "Oxygen reading too high, published -1");
    }
  } else {
    ESP_LOGE(TAG, "Failed to read oxygen data");
  }
}

// -----------------------------
// KeySensor class
// -----------------------------
void KeySensor::update() { 
  this->read_key_data_(); 
}

void KeySensor::read_key_data_() {  
  uint8_t result = 0;
  if (this->read_bytes(GET_KEY_REGISTER, &result, 1)) {
    if (result == 0) {
      oxygen_key = 20.9f / 120.0f;  // Default key
    } else {
      oxygen_key = static_cast<float>(result) / 1000.0f;
    }
    this->publish_state(oxygen_key);
  } else {
    ESP_LOGE(TAG, "Failed to read key data");
  }
}

// -----------------------------
// RealSensor class
// -----------------------------
void RealSensor::calibrate(float new_voltage, float new_millivoltage) { 
  voltage = new_voltage;
  millivoltage = new_millivoltage;

  uint8_t dummy_result = 0;
  if (this->read_bytes(GET_KEY_REGISTER, &dummy_result, 1)) {
    uint8_t calculated_key = 0;
    if (std::abs(millivoltage) < 0.000001f) {
      calculated_key = static_cast<uint8_t>(voltage * 10.0f);
      this->publish_state(1000.0f);  // Just publishing a status
    } else {
      calculated_key = static_cast<uint8_t>((voltage / millivoltage) * 1000.0f);
      this->publish_state(2000.0f);  // Calibration success indicator
    }
    ESP_LOGI(TAG, "Calibration completed: Key = %d", calculated_key);
  } else {
    ESP_LOGE(TAG, "Failed to read during calibration");
  }
}

}  // namespace oxygen_sensor
}  // namespace esphome
