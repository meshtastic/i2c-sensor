#include <Adafruit_I2CDevice.h>
#include <i2c_definitions.h>

Adafruit_I2CDevice i2cDevice = Adafruit_I2CDevice(MT_I2C_ADDRESS);

void handleHasMetric(uint8_t *buffer, uint8_t hasRegister, bool response)
{
    if (buffer[0] == hasRegister) {
        Serial.print("I2C device has(metric) register ");
        Serial.print(hasRegister);
        Serial.print(" with value ");
        Serial.println(response);
        uint8_t buffer[1] = { hasRegister };
        i2cDevice.write(buffer, 1);
    }
}

void handleHasMetrics(uint8_t buffer[1])
{
    /* Set any of these to true if you wish to report them */
    handleHasMetric(buffer, MT_HAS_TEMPERATURE, true);
    handleHasMetric(buffer, MT_HAS_HUMIDITY, false);
    handleHasMetric(buffer, MT_HAS_PRESSURE, false);
    handleHasMetric(buffer, MT_HAS_GAS, false);
    handleHasMetric(buffer, MT_HAS_VOLTAGE, false);
    handleHasMetric(buffer, MT_HAS_CURRENT, false);
    handleHasMetric(buffer, MT_HAS_IAQ, false);
    handleHasMetric(buffer, MT_HAS_DISTANCE, false);
    handleHasMetric(buffer, MT_HAS_LUX, false);
    handleHasMetric(buffer, MT_HAS_WHITE_LUX, false);
    handleHasMetric(buffer, MT_HAS_IR_LUX, false);
    handleHasMetric(buffer, MT_HAS_UV_LUX, false);
    handleHasMetric(buffer, MT_HAS_WIND_DIRECTION, false);
    handleHasMetric(buffer, MT_HAS_WIND_SPEED, false);
    handleHasMetric(buffer, MT_HAS_WEIGHT, false);
    handleHasMetric(buffer, MT_HAS_WIND_GUST, false);
    handleHasMetric(buffer, MT_HAS_WIND_LULL, false);
}

void handleVersion (uint8_t *buffer)
{
    if (buffer[0] == MT_I2C_VERSION) {
        Serial.print("I2C device version: ");
        Serial.println(MT_I2C_VERSION);
        uint8_t *array;
        array = reinterpret_cast<uint8_t*>(1);
        i2cDevice.write(array, 1);
    }
}

void handleFloatMetric(uint8_t *buffer, uint8_t metricRegister, float value)
{
    if (buffer[0] == metricRegister) {
        Serial.print("I2C device metric register ");
        Serial.print(metricRegister);
        Serial.print(" with value ");
        Serial.println(value);

        i2cDevice.write(reinterpret_cast<uint8_t*>(&value), 6);
    }
}

void handleUInt16Metric(uint8_t *buffer, uint8_t metricRegister, uint16_t value)
{
    if (buffer[0] == metricRegister) {
        Serial.print("I2C device metric register ");
        Serial.print(metricRegister);
        Serial.print(" with value ");
        Serial.println(value);

        i2cDevice.write(reinterpret_cast<uint8_t*>(&value), 2);
    }
}

void handleMetrics(uint8_t *buffer) {
    handleFloatMetric(buffer, MT_GET_TEMPERATURE, 25.0);
    handleFloatMetric(buffer, MT_GET_HUMIDITY, 50.0);
    handleFloatMetric(buffer, MT_GET_PRESSURE, 1013.25);
    handleFloatMetric(buffer, MT_GET_GAS, 0.0);
    handleFloatMetric(buffer, MT_GET_VOLTAGE, 3.3);
    handleFloatMetric(buffer, MT_GET_CURRENT, 0.0);
    handleFloatMetric(buffer, MT_GET_IAQ, 0.0);
    handleFloatMetric(buffer, MT_GET_DISTANCE, 0.0);
    handleFloatMetric(buffer, MT_GET_LUX, 0.0);
    handleFloatMetric(buffer, MT_GET_WHITE_LUX, 0.0);
    handleFloatMetric(buffer, MT_GET_IR_LUX, 0.0);
    handleFloatMetric(buffer, MT_GET_UV_LUX, 0.0);
    handleUInt16Metric(buffer, MT_GET_WIND_DIRECTION, 270);
    handleFloatMetric(buffer, MT_GET_WIND_SPEED, 0.0);
    handleFloatMetric(buffer, MT_GET_WEIGHT, 0.0);
    handleFloatMetric(buffer, MT_GET_WIND_GUST, 0.0);
    handleFloatMetric(buffer, MT_GET_WIND_LULL, 0.0);
}


void setup() {
    while (!Serial) { delay(10); }
    Serial.begin(115200);
    Serial.println("Initializing Meshtastic I2C device...");

    if (!i2cDevice.begin()) {
        Serial.println("Attempting to start I2C bus...");
        while (1);
    }
    i2cDevice.write(reinterpret_cast<uint8_t*>(1), 1);
}

void loop() {
    uint8_t buffer[1];
    if (i2cDevice.read(buffer, 1)) {
        handleVersion(buffer);
        handleHasMetrics(buffer);
        handleMetrics(buffer);
    }
    delay(10);
}
