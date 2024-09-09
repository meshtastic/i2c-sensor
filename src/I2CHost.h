#ifndef I2CHOST_H
#define I2CHOST_H

#include <Arduino.h>
#include <I2CDefinitions.h>

#include "generated/telemetry.pb.h"

#include <pb_encode.h>

size_t proto_encode(uint8_t *destbuf, size_t destbufsize, const pb_msgdesc_t *fields, const void *src_struct)
{
    pb_ostream_t stream = pb_ostream_from_buffer(destbuf, destbufsize);
    if (!pb_encode(&stream, fields, src_struct)) {
        return 0;
    } else {
        return stream.bytes_written;
    }
}

/// @brief Send metrics to I2C slave
/// @param metrics Metrics to send
void sendMetrics(meshtastic_EnvironmentMetrics metrics)
{
    uint8_t encoded[meshtastic_EnvironmentMetrics_size];
    size_t encodedSize = proto_encode(encoded, sizeof(encoded), meshtastic_EnvironmentMetrics_fields, &metrics);

    Wire.beginTransmission(MT_I2C_ADDRESS);
    for (size_t i = 0; i < encodedSize; i++)
    {
        Wire.write(encoded[i]);
    }
    Wire.endTransmission();
}

#endif