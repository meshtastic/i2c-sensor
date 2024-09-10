#include <I2CDefinitions.h>
#include <Wire.h>

#if MESHTASTIC_I2C_SENSOR_HOST
#include <I2CHost.h>

meshtastic_EnvironmentMetrics metrics = meshtastic_EnvironmentMetrics_init_zero;

void onReceiveRequest(int numBytes) {
    sendMetrics(metrics);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing Meshtastic I2C Sensor device (master)...");

    Wire.begin(MT_I2C_ADDRESS);
    Wire.beginTransmission(MT_I2C_ADDRESS);
    Wire.write(0x69);
    Wire.endTransmission();
    Wire.onReceive(onReceiveRequest);
}

void loop() {
    metrics.has_temperature = true;
    metrics.temperature = 25.0;
    metrics.has_relative_humidity = true;
    metrics.relative_humidity = 50.0;
    sendMetrics(metrics);
    delay(100);
}
#else
#include <I2CClient.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing Meshtastic I2C Sensor device (client)...");
    Wire.begin(MT_I2C_ADDRESS);
    Wire.onReceive(onReceiveMetrics);
}

void loop() {
    // I2C slave does not need to do anything in the loop
    // Unless you need custom business logic here
    delay(1000);
}
#endif