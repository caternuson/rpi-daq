//---------------------------------------------------------------------------
// ADS1015.h
//
// Header file for class to interface to Adafruit 12 bit ADC which uses the
// TI ADS1015.
// Based on python code found here:
// https://github.com/adafruit/Adafruit-Raspberry-Pi-Python-Code/tree/master/Adafruit_ADS1x15
//
//---------------------------------------------------------------------------
#ifndef ADS1015_H
#define ADS1015_H

#include "I2C.h"
#include <unistd.h>
#include <stdio.h>

class ADS1015 {
    private:
        // Pointer Register
        static const int REG_POINTER_MASK           = 0x03;
        static const int REG_POINTER_CONVERT        = 0x00;
        static const int REG_POINTER_CONFIG         = 0x01;
        static const int REG_POINTER_LOWTHRESH      = 0x02;
        static const int REG_POINTER_HITHRESH       = 0x03;
        
        // Config Register
        static const int REG_CONFIG_OS_MASK         = 0x8000;
        static const int REG_CONFIG_OS_SINGLE       = 0x8000; // Write: Set to start a single-conversion
        static const int REG_CONFIG_OS_BUSY         = 0x0000; // Read: Bit = 0 when conversion is in progress
        static const int REG_CONFIG_OS_NOTBUSY      = 0x8000; // Read: Bit = 1 when device is not performing a conversion
        static const int REG_CONFIG_MUX_MASK        = 0x7000;
        static const int REG_CONFIG_MUX_DIFF_0_1    = 0x0000; // Differential P = AIN0, N = AIN1 (default)
        static const int REG_CONFIG_MUX_DIFF_0_3    = 0x1000; // Differential P = AIN0, N = AIN3
        static const int REG_CONFIG_MUX_DIFF_1_3    = 0x2000; // Differential P = AIN1, N = AIN3
        static const int REG_CONFIG_MUX_DIFF_2_3    = 0x3000; // Differential P = AIN2, N = AIN3
        static const int REG_CONFIG_MUX_SINGLE_0    = 0x4000; // Single-ended AIN0
        static const int REG_CONFIG_MUX_SINGLE_1    = 0x5000; // Single-ended AIN1
        static const int REG_CONFIG_MUX_SINGLE_2    = 0x6000; // Single-ended AIN2
        static const int REG_CONFIG_MUX_SINGLE_3    = 0x7000; // Single-ended AIN3
        static const int REG_CONFIG_PGA_MASK        = 0x0E00;
        static const int REG_CONFIG_PGA_6_144V      = 0x0000; // +/-6.144V range
        static const int REG_CONFIG_PGA_4_096V      = 0x0200; // +/-4.096V range
        static const int REG_CONFIG_PGA_2_048V      = 0x0400; // +/-2.048V range (default)
        static const int REG_CONFIG_PGA_1_024V      = 0x0600; // +/-1.024V range
        static const int REG_CONFIG_PGA_0_512V      = 0x0800; // +/-0.512V range
        static const int REG_CONFIG_PGA_0_256V      = 0x0A00; // +/-0.256V range
        static const int REG_CONFIG_MODE_MASK       = 0x0100;
        static const int REG_CONFIG_MODE_CONTIN     = 0x0000; // Continuous conversion mode
        static const int REG_CONFIG_MODE_SINGLE     = 0x0100; // Power-down single-shot mode (default)
        static const int REG_CONFIG_DR_MASK         = 0x00E0;
        static const int REG_CONFIG_DR_128SPS       = 0x0000; // 128 samples per second
        static const int REG_CONFIG_DR_250SPS       = 0x0020; // 250 samples per second
        static const int REG_CONFIG_DR_490SPS       = 0x0040; // 490 samples per second
        static const int REG_CONFIG_DR_920SPS       = 0x0060; // 920 samples per second
        static const int REG_CONFIG_DR_1600SPS      = 0x0080; // 1600 samples per second (default)
        static const int REG_CONFIG_DR_2400SPS      = 0x00A0; // 2400 samples per second
        static const int REG_CONFIG_DR_3300SPS      = 0x00C0; // 3300 samples per second (also 0x00E0)
        static const int REG_CONFIG_CMODE_MASK      = 0x0010;
        static const int REG_CONFIG_CMODE_TRAD      = 0x0000; // Traditional comparator with hysteresis (default)
        static const int REG_CONFIG_CMODE_WINDOW    = 0x0010; // Window comparator
        static const int REG_CONFIG_CPOL_MASK       = 0x0008;
        static const int REG_CONFIG_CPOL_ACTVLOW    = 0x0000; // ALERT/RDY pin is low when active (default)
        static const int REG_CONFIG_CPOL_ACTVHI     = 0x0008; // ALERT/RDY pin is high when active
        static const int REG_CONFIG_CLAT_MASK       = 0x0004; // Determines if ALERT/RDY pin latches once asserted
        static const int REG_CONFIG_CLAT_NONLAT     = 0x0000; // Non-latching comparator (default)
        static const int REG_CONFIG_CLAT_LATCH      = 0x0004; // Latching comparator
        static const int REG_CONFIG_CQUE_MASK       = 0x0003;
        static const int REG_CONFIG_CQUE_1CONV      = 0x0000; // Assert ALERT/RDY after one conversions
        static const int REG_CONFIG_CQUE_2CONV      = 0x0001; // Assert ALERT/RDY after two conversions
        static const int REG_CONFIG_CQUE_4CONV      = 0x0002; // Assert ALERT/RDY after four conversions
        static const int REG_CONFIG_CQUE_NONE       = 0x0003; // Disable the comparator and put ALERT/RDY in high state (default)

    public:
        ADS1015();
        int readADCSingleEnded(); 
        int readADCSingleEnded(int chan, int pga, int sps);
        
    private:
        I2C i2c;
        int address;
        int regChan(int chan);
        int regPga(int pga);
        int regSps(int sps);
        
};

#endif