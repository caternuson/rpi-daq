//---------------------------------------------------------------------------
// ADS1015.h
//
// I2C class using the /dev interface. Info here:
// https://www.kernel.org/doc/Documentation/i2c/dev-interface
//---------------------------------------------------------------------------
#ifndef I2C_H
#define I2C_H

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>

#define DEFAULT_I2C_BUS "/dev/i2c-1"
#define DEFAULT_I2C_ADDRESS 0x48

class I2C {
  private:
    int file;
    int address;
  public:
    I2C();
    ~I2C();
    int init();
    int init(int addr);
    int init(std::string dev, int addr);
    int shutdown();
    int write_byte(char value);
    int write_byte_data(char reg, char value);
    int write_block_data(char reg, char* values, int length);
    int read_byte();
    int read_byte_data(char reg);
    int read_block_data(char reg, char* values, char length);
};

#endif