#ifndef __I2C_H__
#define __I2C_H__

#include <PortHelper.h>

namespace I2C {

static constexpr bool WRITE{ 0 };
static constexpr bool READ{ 1 };

static constexpr bool ACK{ 0 };
static constexpr bool NACK{ 1 };

#ifdef _AVR_IOM32U4_H_ // Arduino Micro
using SCL = Pin<D,0>;
using SDA = Pin<D,1>;
#else 
#error "I2C.h needs SCL/SDA pin definitions, but doesn't recognize the current hardware"
#endif

void delay() {
    _delay_us(2); // TODO - delay timings
}

template<typename P>
void setPinAndWait(bool b) {
    if (b) {
        // Go to input mode then use the internal pull-up resistor to raise the voltage
        // (don't connect directly to high voltage, since the peer can short circuit by pulling down)
        P::input();
        P::enable();
    } else {
        // Go to output mode then connect to ground to drop the voltage
        P::disable();
        P::output();
    }
    delay(); // propagation delay
}
static constexpr auto set_SDA = setPinAndWait<SDA>;
static constexpr auto set_SCL = setPinAndWait<SCL>;

void sendBit(bool b) {
    set_SDA(b);
    set_SCL(true);
    set_SCL(false);
}

bool receiveBit() {
    set_SDA(true); // enable internal pull-up for peer to (maybe) pull down
    set_SCL(true);
    auto val{ SDA::get() };
    set_SCL(false);
    return val;
}

void init() {
    // Designate SDA and SCL as an input pins with internal pull-up resistors enabled
    SDA::input(); SDA::enable();
    SCL::input(); SCL::enable();
    delay();
}

void start() {
    set_SDA(false); // signal START with falling SDA edge while SCL is high
    set_SCL(false); // pull SCL low before beginning to transmit
}

void stop() {
    set_SDA(false);
    set_SCL(true);
    set_SDA(true); // signal STOP with rising SDA edge while SCL is high
}

template<uint8_t peerAddr>
auto writeByte(uint8_t data) -> bool /* success */ {
    start();
    // send 7-bit peer address, higher bits first
    for (uint8_t b{ 7 }; b > 0; --b) {
        sendBit(peerAddr & (1 << (b-1)));
    }
    sendBit(WRITE); // Indicate that we will send data to the peer
    if (receiveBit() == NACK) { // get acknowledgement from peer
        stop();
        return false; // indicate that the write failed
    }
    // send 8 data bits, high bits first
    for (uint8_t b{ 0 }; b < 8; ++b) {
        sendBit(data & (1 << (7-b)));
    }
    auto result{ receiveBit() };
    stop();
    return result == ACK;
}

} // namespace I2C

#endif
