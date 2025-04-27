#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

// Reference:
// https://github.com/DFRobot/DFRobot_OxygenSensor

namespace esphome {
namespace oxygen_sensor {

// Sensor Register Addresses
static const uint8_t OXYGEN_DATA_REGISTER = 0x03;
static const uint8_t USER_SET_REGISTER    = 0x08;
static const uint8_t AUTUAL_SET_REGISTER  = 0x09;
static const uint8_t GET_KEY_REGISTER     = 0x0A;
static const uint8_t OXYGEN_COUNT         = 100; // Oxygen count value

// I2C Device Addresses
static const uint8_t ADDRESS_0 = 0x70;
static const uint8_t ADDRESS_1 = 0x71;
static const uint8_t ADDRESS_2 = 0x72;
static const uint8_t ADDRESS_3 = 0x73; // I2C Slave Address select

// Forward declarations of classes
class OxygenSensor;
class KeySensor;
class RealSensor;

// -----------------------------
// OxygenSensor Class
// -----------------------------
class OxygenSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  // Constructor
  using sensor::Sensor::Sensor;

  // Called periodically to update sensor data
  void update() override;

 protected:
  // Internal function to read oxygen data
  void read_data_();
};

// -----------------------------
// KeySensor Class
// -----------------------------
class KeySensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  using sensor::Sensor::Sensor;

  void update() override;

 protected:
  void read_data_();
};

// -----------------------------
// RealSensor Class
// -----------------------------
class RealSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  using sensor::Sensor::Sensor;

  // You can expose calibrate() publicly if you want to call it manually
  void calibrate(float voltage, float millivoltage);

  // Optional: Add an override if you want RealSensor to update itself periodically
  // void update() override;

 protected:
  // Internal calibration logic
  // void read_data_();
};

}  // namespace oxygen_sensor
}  // namespace esphome
