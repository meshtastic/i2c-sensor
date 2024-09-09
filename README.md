# Meshtastic I2C Sensor

This readme provides instructions on how to build / use a Meshtastic I2C sensor in both host and client modes.

## Host Mode

To use the I2C sensor in host mode, follow these steps:

1. Use the boilerplate example code in `src/main.cpp` under, gaurded by the `MESHTASTIC_I2C_SENSOR_HOST=1` macro to create your custom Meshtastic I2C sensor sketch.
2. Upload to your board.
3. Connect your custom Meshtastic I2C sensor to the Meshtastic device over I2C.
4. Enable environment telemetry (`telemetry.environment_measurement_enabled`).

### Host MCU support

There are two PlatformIO environments available as examples to build off of: `kb2040_host` and `kb2040_client` which build the main example sketch in host and client mode respectively. You can add your own PlatformIO environments theoretically for pretty much any device capable of I2C. This may require modification to the host codebase, which serves as a boilerplate for your own custom implementation.

## Client Library

This is used in the Meshtastic firmware to consume any custom sensor data you supply from the Host boilerplate above.
Example code is in `src/main.cpp` under, gaurded by the `MESHTASTIC_I2C_SENSOR_HOST=0` macro:

```
void setup() {
    while (!Serial) { delay(10); }
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
```
