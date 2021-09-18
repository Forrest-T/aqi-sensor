#include <avr/io.h>

#define F_CPU 16000000
#define BLINK_DELAY_MS 1000

#include <util/delay.h>

int main() {
    DDRD = 0b10;
    while (true) {
        PORTD |= 0b10;
        _delay_ms(BLINK_DELAY_MS);
        PORTD &= ~0b10;
        _delay_ms(BLINK_DELAY_MS);
    }
}
