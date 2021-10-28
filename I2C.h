#ifndef __I2C_H__
#define __I2C_H__

#ifdef _AVR_IOM32U4_H_ // Arduino Micro
using SCL = Pin<D,0>;
using SDA = Pin<D,1>;
#else 
#error "I2C.h needs SCL/SDA pin definitions, but doesn't recognize the current hardware"
#endif


#endif
