#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#include <PortHelper.h>
#include <I2C.h>

int main() {
    _delay_ms(500);
    I2C::init();

    auto received{ I2C::writeByte<0x27>(0x00) }; // send a test byte

    Pin<D,1>::output();
    if (received) {
        while (true) { // blink slowly to indicate success
            Pin<D,1>::enable(); _delay_ms(1000);
            Pin<D,1>::disable(); _delay_ms(1000);
        }
    } else {
        while (true) { // blink quickly to indicate failure
            Pin<D,1>::enable(); _delay_ms(300);
            Pin<D,1>::disable(); _delay_ms(300);
        }
    }
}
