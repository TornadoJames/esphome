#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

// ref:
// https://github.com/DFRobot/DFRobot_OzoneSensor

namespace esphome {
namespace oxygens_sensor {
// Sensor Mode
// While passive is supposedly supported, it does not appear to work reliably.
static const uint8_t SENSOR_MODE_REGISTER = 0x03;
static const uint8_t SENSOR_MODE_AUTO = 0x00;
static const uint8_t SENSOR_MODE_PASSIVE = 0x01;
static const uint8_t SET_REGISTER = 0x04;

// Each register is 2 wide, so 0x07-0x08 for passive, or 0x09-0x0A for auto
// First register is high bits, next low.
static const uint8_t SENSOR_PASS_READ_REG = 0x07;
static const uint8_t SENSOR_AUTO_READ_REG = 0x09;

class OxygensSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  void update() override;
  void dump_config() override;
  void setup() override;

 protected:
  void read_data_();
};

}  // namespace sen0321_sensor
}  // namespace esphome

// #ifndef __OxygensSensor_H__
// #define __OxygensSensor_H__

// #include <Arduino.h>
// #include <Wire.h>

// namespace esphome {
// namespace oxygens_sensor {

// #define ADDRESS_0   0x70
// #define ADDRESS_1   0x71
// #define ADDRESS_2   0x72
// #define ADDRESS_3   0x73  ///< iic slave Address select
// #define OCOUNT      100   ///< oxygen Count Value
// #define OXYGEN_DATA_REGISTER 0x03   ///< register for oxygen data
// #define USER_SET_REGISTER    0x08   ///< register for users to configure key value manually
// #define AUTUAL_SET_REGISTER  0x09   ///< register that automatically configure key value
// #define GET_KEY_REGISTER     0x0A   ///< register for obtaining key value

// class OxygensSensor
// {
// public:
//   OxygensSensor(TwoWire *pWire = &Wire);
//   ~OxygensSensor();
//   /**
//    * @fn begin
//    * @brief Initialize i2c
//    * @param addr i2c device address
//    * @n     Default to use i2c address of 0x70 without passing parameters
//    * @return None
//    */
//   bool begin(uint8_t addr = ADDRESS_0);

//   /**
//    * @fn calibrate
//    * @brief Calibrate oxygen sensor
//    * @param vol oxygen concentration unit vol
//    * @param mv calibrated voltage unit mv
//    * @return None
//    */
//   void calibrate(float vol, float mv = 0);

//   /**
//    * @fn getOxygenData
//    * @brief Get oxygen concentration
//    * @param collectNum The number of data to be smoothed
//    * @n     For example, upload 20 and take the average value of the 20 data, then return the concentration data
//    * @return Oxygen concentration, unit
//    */  
//   float getOxygenData(uint8_t collectNum);
  
// private:
//   void readFlash();
//   void i2cWrite(uint8_t reg, uint8_t data);
//   uint8_t  _addr;                               
//   float _Key = 0.0;                          ///< oxygen key value
//   float oxygenData[OCOUNT] = {0.00};
//   float getAverageNum(float bArray[], uint8_t len);
//   TwoWire *_pWire;
// };
// #endif
