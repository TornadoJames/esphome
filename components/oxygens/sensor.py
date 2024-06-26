import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    ICON_WIFI,
    UNIT_PERCENT,
    STATE_CLASS_MEASUREMENT,
)

CODEOWNERS = ["@tornadojames"]
DEPENDENCIES = ["i2c"]

oxygens_sensor_ns = cg.esphome_ns.namespace("oxygens_sensor")
OxygensSensor = oxygens_sensor_ns.class_(
    "OxygensSensor", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        OxygensSensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_WIFI,
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
