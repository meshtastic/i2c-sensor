#include <I2CDefinitions.h>
#include <Wire.h>

#if MESHTASTIC_I2C_MASTER
#include <I2CHandlers.h>

void setup() {
    while (!Serial) { delay(10); }
    Serial.begin(115200);
    Serial.println("Initializing Meshtastic I2C Sensor device (master)...");

    if (!i2cDevice.begin(MT_I2C_VERSION)) {
        Serial.println("Attempting to start I2C bus...");
        while (1);
    }
    i2cDevice.write(reinterpret_cast<uint8_t*>(MT_I2C_VERSION), 1);
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
#else
#include <I2CRequests.h>

void setup() {
    while (!Serial) { delay(10); }
    Serial.begin(115200);
    Serial.println("Initializing Meshtastic I2C Sensor device (slave)...");

    Wire.begin(MT_I2C_ADDRESS);
}

void loop() {
    uint8_t buffer[1];
    if (Wire.available()) {
        auto version = getMeshtasticI2cVersion();
        if (version > 0) {
            Serial.print("Meshtastic I2C device version");
            Serial.println(version);

            if (hasTemperature()) {
                auto temperature = getTemperature();
                Serial.print("Temperature: ");
                Serial.println(temperature);
            }
        }
    }
    delay(1000);
}
#endif