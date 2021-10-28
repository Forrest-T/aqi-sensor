#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#include <PortHelper.h>
#include <I2C.h>

int main() {
    _delay_ms(500);
    I2C::init();

    // Instruction byte format
    // b0: RS (register select) { 0: instruction, 1: data }
    // b1: RW (read/write)      { 0: write, 1: read }
    // b2: E  (enable)          { rising edge: commit }
    // b3: BL (backlight)       { 0: disable, 1: enable }
    // b4: D4 (data)
    // b5: D5 (data)
    // b6: D6 (data)
    // b7: D7 (data)

    // Function set 1/3
    I2C::writeByte<0x27>(0x30); // write value 
    I2C::writeByte<0x27>(0x34); // commit value with rising edge on E bit
    I2C::writeByte<0x27>(0x30); // falling edge for next instruction
    _delay_ms(20);
    // Function set 2/3
    I2C::writeByte<0x27>(0x30);
    I2C::writeByte<0x27>(0x34);
    I2C::writeByte<0x27>(0x30);
    _delay_ms(20);
    // Function set 3/3
    I2C::writeByte<0x27>(0x30);
    I2C::writeByte<0x27>(0x34);
    I2C::writeByte<0x27>(0x30);
    _delay_ms(20);

    // Go to 4-bit mode
    I2C::writeByte<0x27>(0x20);
    I2C::writeByte<0x27>(0x24);
    I2C::writeByte<0x27>(0x20);
    _delay_ms(20);

    // We're now in 4-bit mode, but need to write 8-bit instructions.
    // We can pair two back-to-back writes: high 4 bits, then low 4 bits

    // Choose two-line mode with 5x7 pixel font
    I2C::writeByte<0x27>(0x20);
    I2C::writeByte<0x27>(0x24); // commit high bits (0x2_)
    I2C::writeByte<0x27>(0x20);
    _delay_ms(20);
    I2C::writeByte<0x27>(0x80);
    I2C::writeByte<0x27>(0x84); // commit low bits (0x_8) + instruction takes effect
    I2C::writeByte<0x27>(0x80);
    _delay_ms(20);

    // Display control (values from spec)
    I2C::writeByte<0x27>(0x00);
    I2C::writeByte<0x27>(0x04);
    I2C::writeByte<0x27>(0x00);
    _delay_ms(20);
    I2C::writeByte<0x27>(0x80);
    I2C::writeByte<0x27>(0x84);
    I2C::writeByte<0x27>(0x80);
    _delay_ms(20);

    // Clear display
    I2C::writeByte<0x27>(0x00);
    I2C::writeByte<0x27>(0x04);
    I2C::writeByte<0x27>(0x00);
    _delay_ms(20);
    I2C::writeByte<0x27>(0x10);
    I2C::writeByte<0x27>(0x14);
    I2C::writeByte<0x27>(0x10);
    _delay_ms(20);

    // Entry mode set
    I2C::writeByte<0x27>(0x00);
    I2C::writeByte<0x27>(0x04);
    I2C::writeByte<0x27>(0x00);
    _delay_ms(20);
    I2C::writeByte<0x27>(0x60);
    I2C::writeByte<0x27>(0x64);
    I2C::writeByte<0x27>(0x60);
    _delay_ms(20);

    // Display control
    I2C::writeByte<0x27>(0x08);
    I2C::writeByte<0x27>(0x0c);
    I2C::writeByte<0x27>(0x08);
    _delay_ms(20);
    I2C::writeByte<0x27>(0xf8);
    I2C::writeByte<0x27>(0xfc);
    I2C::writeByte<0x27>(0xf8);
    _delay_ms(20);

    Pin<D,1>::output();
    while (true) { // blink to indicate we are done
        Pin<D,1>::enable(); _delay_ms(1000);
        Pin<D,1>::disable(); _delay_ms(1000);
    }
}
