import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    ICON_MOLECULE_OXYGEN,
    UNIT_PERCENT,
    STATE_CLASS_MEASUREMENT,
)

CODEOWNERS = ["@tornadojames"]
DEPENDENCIES = ["i2c"]

# Create a namespace for your sensor
oxygens_sensor_ns = cg.esphome_ns.namespace("oxygens_sensor")

# Define classes from C++ (matching your C++ header!)
OxygensSensor = oxygens_sensor_ns.class_(
    "OxygensSensor", cg.PollingComponent, i2c.I2CDevice
)
KeySensor = oxygens_sensor_ns.class_(
    "KeySensor", cg.PollingComponent, i2c.I2CDevice
)
RealSensor = oxygens_sensor_ns.class_(
    "RealSensor", cg.PollingComponent, i2c.I2CDevice
)

# Define configuration schemas for each sensor
OXYGENS_SENSOR_SCHEMA = (
    sensor.sensor_schema(
        OxygensSensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_MOLECULE_OXYGEN,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(i2c.i2c_device_schema(address=0x73))
)

KEY_SENSOR_SCHEMA = (
    sensor.sensor_schema(
        KeySensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_MOLECULE_OXYGEN,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(i2c.i2c_device_schema(address=0x73))  # Same bus address unless using different
)

REAL_SENSOR_SCHEMA = (
    sensor.sensor_schema(
        RealSensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_MOLECULE_OXYGEN,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(i2c.i2c_device_schema(address=0x73))
)

# Main config schema
CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required("oxygen"): OXYGEN_SENSOR_SCHEMA,
        cv.Optional("key"): KEY_SENSOR_SCHEMA,
        cv.Optional("real"): REAL_SENSOR_SCHEMA,
    }
)

# Code generation logic
async def to_code(config):
    if "oxygen" in config:
        oxygen_var = await sensor.new_sensor(config["oxygen"])
        await cg.register_component(oxygen_var, config["oxygen"])
        await i2c.register_i2c_device(oxygen_var, config["oxygen"])

    if "key" in config:
        key_var = await sensor.new_sensor(config["key"])
        await cg.register_component(key_var, config["key"])
        await i2c.register_i2c_device(key_var, config["key"])

    if "real" in config:
        real_var = await sensor.new_sensor(config["real"])
        await cg.register_component(real_var, config["real"])
        await i2c.register_i2c_device(real_var, config["real"])
