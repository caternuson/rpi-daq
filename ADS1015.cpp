//---------------------------------------------------------------------------
// ADS1015.cpp
//
// Class to interface to Adafruit 12 bit ADC.
// Based on python code found here:
// https://github.com/adafruit/Adafruit-Raspberry-Pi-Python-Code/tree/master/Adafruit_ADS1x15
//
//---------------------------------------------------------------------------
#include "ADS1015.h"

ADS1015::ADS1015() {
    i2c = I2C();
}

int ADS1015::readADCSingleEnded() {
    return readADCSingleEnded(0, 6144, 250);
}

int ADS1015::readADCSingleEnded(int chan, int pga, int sps) {
    unsigned int config;
    config =    REG_CONFIG_CQUE_NONE    | \
                REG_CONFIG_CLAT_NONLAT  | \
                REG_CONFIG_CPOL_ACTVLOW | \
                REG_CONFIG_CMODE_TRAD   | \
                REG_CONFIG_MODE_SINGLE;
    
    config |= regPga(pga);
    config |= regSps(sps);
    config |= regChan(chan);
    
    config |= REG_CONFIG_OS_SINGLE;
    
    char data[2];
    data[0] = (config >> 8) & 0xFF;
    data[1] = config & 0xFF;
    
    //printf("write return %i\n",i2c.write_block_data(REG_POINTER_CONFIG, data, 2));
    i2c.write_block_data(REG_POINTER_CONFIG, data, 2);

    usleep(4100);
    
    char result[2];
    //printf("read return %i\n",i2c.read_block_data(REG_POINTER_CONVERT, result, 2));
    i2c.read_block_data(REG_POINTER_CONVERT, result, 2);
    
    return ( ((result[0] << 8) | (result[1] & 0xFF)) >> 4 ) * pga/2048.0;
}

int ADS1015::regChan(int chan) {
    switch (chan) {
        case 1: return REG_CONFIG_MUX_SINGLE_1;
        case 2: return REG_CONFIG_MUX_SINGLE_2;
        case 3: return REG_CONFIG_MUX_SINGLE_3;
        default: return REG_CONFIG_MUX_SINGLE_0;    
    }
}

int ADS1015::regSps(int sps) {
    switch (sps) {
        case 128:   return REG_CONFIG_DR_128SPS;
        case 250:   return REG_CONFIG_DR_250SPS;
        case 490:   return REG_CONFIG_DR_490SPS;
        case 920:   return REG_CONFIG_DR_920SPS;
        case 1600:  return REG_CONFIG_DR_1600SPS;
        case 2400:  return REG_CONFIG_DR_2400SPS;
        case 3300:  return REG_CONFIG_DR_3300SPS;
        default:    return REG_CONFIG_DR_250SPS;
    }
}

int ADS1015::regPga(int pga) {
    switch (pga) {
        case 6144:  return REG_CONFIG_PGA_6_144V;
        case 4096:  return REG_CONFIG_PGA_4_096V;
        case 2048:  return REG_CONFIG_PGA_2_048V;
        case 1024:  return REG_CONFIG_PGA_1_024V;
        case 512:   return REG_CONFIG_PGA_0_512V;
        case 256:   return REG_CONFIG_PGA_0_256V;
        default:    return REG_CONFIG_PGA_6_144V;
    }
}