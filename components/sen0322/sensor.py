import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    ICON_PERCENT,
    UNIT_PERCENT,
    STATE_CLASS_MEASUREMENT,
)

CODEOWNERS = ["@tornadojames"]
DEPENDENCIES = ["i2c"]

sen0321_sensor_ns = cg.esphome_ns.namespace("sen0322_sensor")
Sen0321Sensor = sen0322_sensor_ns.class_(
    "Sen0322Sensor", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        Sen0322Sensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_PERCENT,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x73))
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
