#include <avr/io.h>

#define F_CPU 16000000
#define BLINK_DELAY_MS 1000

#include <util/delay.h>

int main() {
    DDRB = 0b10000;
    while (true) {
        PORTB |= 0b10000;
        _delay_ms(BLINK_DELAY_MS);
        PORTB &= ~0b10000;
        _delay_ms(BLINK_DELAY_MS);
    }
}
