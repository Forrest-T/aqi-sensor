#ifndef __PORT_HELPER_H__
#define __PORT_HELPER_H__

enum Port {
    B = 0,
    C = 1,
    D = 2,
};

template< Port P, int Bit >
class Pin {
    static_assert( Bit >= 0 && Bit <= 7, "Bit in range" );
    static_assert( P >= 0 /* B */ && P <= 2 /* D */, "Port is valid" );
    static constexpr decltype(&DDRD) Direction[3] {
        [B] = &DDRB, [C] = &DDRC, [D] = &DDRD
    };
    static constexpr decltype(&PORTD) WritePin[3] {
        [B] = &PORTB, [C] = &PORTC, [D] = &PORTD
    };
    static constexpr decltype(&PIND) ReadPin[3] {
        [B] = &PINB, [C] = &PINC, [D] = &PIND
    };
public:
    // Designate pin as input or output
    static void output() { *Direction[P] |= ( 1 << Bit ); }
    static void input()  { *Direction[P] &= ~( 1 << Bit ); }
    // Write pin value
    static void enable()  { *WritePin[P] |= ( 1 << Bit ); }
    static void disable() { *WritePin[P] &= ~( 1 << Bit ); }
    static void set(bool b) {
        if (b) {
            enable();
        } else {
            disable();
        }
    }
    // Read pin value
    static bool get() { return *ReadPin[P] & (1 << Bit); }
};

#endif
