#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#include <PortHelper.h>

constexpr auto BLINK_DELAY_MS{ 1000 };

int main() {
    Pin<D,1>::isOutput();
    while (true) {
        Pin<D,1>::set();
        _delay_ms(BLINK_DELAY_MS);
        Pin<D,1>::unset();
        _delay_ms(BLINK_DELAY_MS);
    }
}
