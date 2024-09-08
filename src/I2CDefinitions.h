#ifndef I2CDefinitions_h
#define I2CDefinitions_h

#include <Adafruit_I2CDevice.h>

#define MT_I2C_ADDRESS 0x69
#define MT_I2C_VERSION 1

Adafruit_I2CDevice i2cDevice = Adafruit_I2CDevice(MT_I2C_ADDRESS);

#define MT_HAS_TEMPERATURE 0x10
#define MT_GET_TEMPERATURE 0x11
#define MT_HAS_HUMIDITY 0x20
#define MT_GET_HUMIDITY 0x21
#define MT_HAS_PRESSURE 0x30
#define MT_GET_PRESSURE 0x31
#define MT_HAS_GAS 0x40
#define MT_GET_GAS 0x41
#define MT_HAS_VOLTAGE 0x50
#define MT_GET_VOLTAGE 0x51
#define MT_HAS_CURRENT 0x60
#define MT_GET_CURRENT 0x61
#define MT_HAS_IAQ 0x70
#define MT_GET_IAQ 0x71
#define MT_HAS_DISTANCE 0x80
#define MT_GET_DISTANCE 0x81
#define MT_HAS_LUX 0x90
#define MT_GET_LUX 0x91
#define MT_HAS_WHITE_LUX 0xA0
#define MT_GET_WHITE_LUX 0xA1
#define MT_HAS_IR_LUX 0xB0
#define MT_GET_IR_LUX 0xB1
#define MT_HAS_UV_LUX 0xC0
#define MT_GET_UV_LUX 0xC1
#define MT_HAS_WIND_DIRECTION 0xD0
#define MT_GET_WIND_DIRECTION 0xD1
#define MT_HAS_WIND_SPEED 0xE0
#define MT_GET_WIND_SPEED 0xE1
#define MT_HAS_WEIGHT 0xF0
#define MT_GET_WEIGHT 0xF1
#define MT_HAS_WIND_GUST 0x010
#define MT_GET_WIND_GUST 0x011
#define MT_HAS_WIND_LULL 0x020
#define MT_GET_WIND_LULL 0x021

#endif