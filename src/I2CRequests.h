#ifndef I2C_REQUESTS_H
#define I2C_REQUESTS_H

#pragma once
#include <Arduino.h>
#include <I2CDefinitions.h>
#include <Wire.h>

#include "generated/telemetry.pb.h"

#include <pb_decode.h>

bool proto_decode(const uint8_t *srcbuf, size_t srcbufsize, const pb_msgdesc_t *fields, void *dest_struct)
{
    pb_istream_t stream = pb_istream_from_buffer(srcbuf, srcbufsize);
    if (!pb_decode(&stream, fields, dest_struct)) {
        return false;
    } else {
        return true;
    }
}

/// @brief Last metrics received
static meshtastic_EnvironmentMetrics lastMetricsRecieved = meshtastic_EnvironmentMetrics_init_zero;

/// @brief On receive metrics from I2C master
/// @param length Number of bytes received over I2C
void onReceiveMetrics(int length)
{
    Serial.println("Receiving metrics");
    uint8_t buffer[meshtastic_EnvironmentMetrics_size];
    Wire.readBytes(buffer, length);
    meshtastic_EnvironmentMetrics metrics = meshtastic_EnvironmentMetrics_init_zero;
    proto_decode(buffer, meshtastic_EnvironmentMetrics_size, meshtastic_EnvironmentMetrics_fields, &metrics);

    // Uncomment to print received metrics
    // if (metrics.has_temperature) {
    //     Serial.print("Temperature: ");
    //     Serial.println(metrics.temperature);
    // }
    lastMetricsRecieved = metrics;
}

#endif // I2C_REQUESTS_H