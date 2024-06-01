#include "oxygens.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace oxygens_sensor {

static const char *const TAG = "oxygens_sensor.sensor";

void OxygensSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up oxygens...");
  if (!this->write_byte(SENSOR_MODE_REGISTER, SENSOR_MODE_AUTO)) {
    ESP_LOGW(TAG, "Error setting measurement mode.");
    this->mark_failed();
  };
}

void OxygensSensor::update() { 
  this->read_data_(); 
}

void OxygensSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "DF Robot Oxygen Sensor sen0322:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with sen0322 failed!");
  }
  LOG_UPDATE_INTERVAL(this);
}

void OxygensSensor::read_data_() {
  uint8_t result[2];
  this->read_bytes(OXYGEN_DATA_REGISTER, result, (uint8_t) 3);
  this->publish_state(((uint16_t) (result[0]) + result[1] / 10.0 + result[2] / 100.0));

}  // namespace oxygens_sensor
}  // namespace esphome

// OxygensSensor::OxygensSensor(TwoWire *pWire)
// {
//   this->_pWire = pWire;
// }

// OxygensSensor::~OxygensSensor()
// {
//   this->_pWire = NULL;
// }

// bool OxygensSensor::begin(uint8_t addr)
// {
//   this->_addr = addr;
//   _pWire->begin();
//   _pWire->beginTransmission(_addr);
//   if(_pWire->endTransmission() == 0){
//     return true;
//   }
//   return false;
// }

// void OxygensSensor::readFlash()
// {
//   uint8_t value = 0;
//   _pWire->beginTransmission(_addr);
//   _pWire->write(GET_KEY_REGISTER);
//   _pWire->endTransmission();
//   delay(50);
//   _pWire->requestFrom(_addr, (uint8_t)1);
//     while (_pWire->available()){
//       value = _pWire->read();
//     }
//   if(value == 0){
//     this->_Key = 20.9 / 120.0;
//   }else{
//     this->_Key = (float)value / 1000.0;
//   }
// }

// void OxygensSensor::i2cWrite(uint8_t reg, uint8_t data)
// {
//   _pWire->beginTransmission(_addr);
//   _pWire->write(reg);
//   _pWire->write(data);
//   _pWire->endTransmission();
// }

// void OxygensSensor::calibrate(float vol, float mv)
// {
//   uint8_t keyValue = vol * 10;
//   if(mv < 0.000001 && mv > (-0.000001) ) {
//     i2cWrite(USER_SET_REGISTER, keyValue);
//   }else {
//     keyValue = (vol / mv) * 1000;
//     i2cWrite(AUTUAL_SET_REGISTER, keyValue);
//   }
// }

// float OxygensSensor::getOxygenData(uint8_t collectNum)
// {
//   uint8_t rxbuf[10]={0}, k = 0;
//   static uint8_t i = 0, j = 0;
//   readFlash();
//   if(collectNum > 0){
//     for(j = collectNum - 1;  j > 0; j--) {  oxygenData[j] = oxygenData[j-1]; }
//     _pWire->beginTransmission(_addr);
//     _pWire->write(OXYGEN_DATA_REGISTER);
//     _pWire->endTransmission();
//     delay(100);
//     _pWire->requestFrom(_addr, (uint8_t)3);
//       while (_pWire->available()){
//         rxbuf[k++] = _pWire->read();
//       }
//     oxygenData[0] = ((_Key) * (((float)rxbuf[0]) + ((float)rxbuf[1] / 10.0) + ((float)rxbuf[2] / 100.0)));
//     if(i < collectNum) i++;
//     return getAverageNum(oxygenData, i);
//   }else {
//     return -1.0;
//   }
// }

// float OxygensSensor::getAverageNum(float bArray[], uint8_t len)
// {
//   uint8_t i = 0;
//   double bTemp = 0;
//   for(i = 0; i < len; i++) {
//     bTemp += bArray[i];
//   }
//   return bTemp / (float)len;
// }
