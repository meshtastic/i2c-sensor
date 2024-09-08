#ifndef I2C_REQUESTS_H
#define I2C_REQUESTS_H

#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <I2CDefinitions.h>

uint8_t getMeshtasticI2cVersion()
{
    uint8_t writeBuffer[1] = { MT_I2C_VERSION };
    uint8_t readBuffer[1];
    i2cDevice.write_then_read(writeBuffer, 1, readBuffer, 1);
    return readBuffer[0];
}

bool requestHasMetric(uint8_t hasRegister)
{
    uint8_t writeBuffer[1] = { hasRegister };
    uint8_t readBuffer[1];
    i2cDevice.write_then_read(writeBuffer, 1, readBuffer, 1);
    return readBuffer[0] > 0;
}

float requestFloatMetric(uint8_t metricRegister)
{
    uint8_t writeBuffer[1] = { metricRegister };
    float readBuffer;
    i2cDevice.write_then_read(writeBuffer, 1, reinterpret_cast<uint8_t*>(&readBuffer), 6);
    return readBuffer;
}

uint16_t requestUInt16Metric(uint8_t metricRegister)
{
    uint8_t writeBuffer[1] = { metricRegister };
    uint16_t readBuffer;
    i2cDevice.write_then_read(writeBuffer, 1, reinterpret_cast<uint8_t*>(&readBuffer), 2);
    return readBuffer;
}

bool hasTemperature() { return requestHasMetric(MT_HAS_TEMPERATURE); }
bool hasHumidity() { return requestHasMetric(MT_HAS_HUMIDITY); }
bool hasPressure() { return requestHasMetric(MT_HAS_PRESSURE); }
bool hasGas() { return requestHasMetric(MT_HAS_GAS); }
bool hasVoltage() { return requestHasMetric(MT_HAS_VOLTAGE); }
bool hasCurrent() { return requestHasMetric(MT_HAS_CURRENT); }
bool hasIAQ() { return requestHasMetric(MT_HAS_IAQ); }
bool hasDistance() { return requestHasMetric(MT_HAS_DISTANCE); }
bool hasLux() { return requestHasMetric(MT_HAS_LUX); }
bool hasWhiteLux() { return requestHasMetric(MT_HAS_WHITE_LUX); }
bool hasIRLux() { return requestHasMetric(MT_HAS_IR_LUX); }
bool hasUVLux() { return requestHasMetric(MT_HAS_UV_LUX); }
bool hasWindDirection() { return requestHasMetric(MT_HAS_WIND_DIRECTION); }
bool hasWindSpeed() { return requestHasMetric(MT_HAS_WIND_SPEED); }
bool hasWeight() { return requestHasMetric(MT_HAS_WEIGHT); }
bool hasWindGust() { return requestHasMetric(MT_HAS_WIND_GUST); }
bool hasWindLull() { return requestHasMetric(MT_HAS_WIND_LULL); }

float getTemperature() { return requestFloatMetric(MT_GET_TEMPERATURE); }
float getHumidity() { return requestFloatMetric(MT_GET_HUMIDITY); }
float getPressure() { return requestFloatMetric(MT_GET_PRESSURE); }
float getGas() { return requestFloatMetric(MT_GET_GAS); }
float getVoltage() { return requestFloatMetric(MT_GET_VOLTAGE); }
float getCurrent() { return requestFloatMetric(MT_GET_CURRENT); }
float getIAQ() { return requestFloatMetric(MT_GET_IAQ); }
float getDistance() { return requestFloatMetric(MT_GET_DISTANCE); }
float getLux() { return requestFloatMetric(MT_GET_LUX); }
float getWhiteLux() { return requestFloatMetric(MT_GET_WHITE_LUX); }
float getIRLux() { return requestFloatMetric(MT_GET_IR_LUX); }
float getUVLux() { return requestFloatMetric(MT_GET_UV_LUX); }
float getWindDirection() { return requestFloatMetric(MT_GET_WIND_DIRECTION); }
float getWindSpeed() { return requestFloatMetric(MT_GET_WIND_SPEED); }
float getWeight() { return requestFloatMetric(MT_GET_WEIGHT); }
float getWindGust() { return requestFloatMetric(MT_GET_WIND_GUST); }
float getWindLull() { return requestFloatMetric(MT_GET_WIND_LULL); }

#endif // I2C_REQUESTS_H