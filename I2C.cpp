//---------------------------------------------------------------------------
// I2C.cpp
//
// I2C class using the /dev interface. Info here:
// https://www.kernel.org/doc/Documentation/i2c/dev-interface
//---------------------------------------------------------------------------
#include "I2C.h"

I2C::I2C() {
    file = -1;
    address = -1;
}

I2C::~I2C() {
    shutdown();
}

int I2C::init() {
    return init(DEFAULT_I2C_BUS, DEFAULT_I2C_ADDRESS); 
}

int I2C::init(int addr) {
    return init(DEFAULT_I2C_BUS, addr);
}

int I2C::init(std::string dev, int addr) {
    address = addr;
    file = open(dev.c_str(), O_RDWR);
    if (file < 0) {
        return -1;
    }
    ioctl(file, I2C_SLAVE, address);
    return 0;   
}

int I2C::shutdown() {
    if (file < 0) {
        return -1;
    }
    return close(file);
}

int I2C::write_byte(char value) {
    char buf[1];
    buf[0] = value;
    if (write(file, buf, 1) != 1) {
        return -1;
    }
    return 0;
}

int I2C::write_byte_data(char reg, char value) {
    char buf[2];
    buf[0] = reg;
    buf[1] = value;
    if (write(file, buf, 2) != 2) {
        return -1;
    }
    return 0;
}

int I2C::write_block_data(char reg, char* values, int length) {
    unsigned int buf_size = length+1;
    char buf[buf_size];
    buf[0] = reg;
    for(int i=0; i<length; i++) {
        buf[i+1] = values[i]; 
    }
    if (write(file, buf, buf_size) != buf_size) {
        return -1;
    }
    return 0;
}

int I2C::read_byte() {
    char buf[1];
    if (read(file, buf, 1) != 1) {
        return -1;
    }
    return buf[0];
}

int I2C::read_byte_data(char reg) {
    write_byte(reg);
    return read_byte();
}

int I2C::read_block_data(char reg, char* values, char length) {
    write_byte(reg);
    return read(file, values, length);
}
