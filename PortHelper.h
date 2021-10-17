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
    static constexpr decltype(&PORTD) Port[3] {
        [B] = &PORTB, [C] = &PORTC, [D] = &PORTD
    };
public:
    static void set()   { *Port[P] |= ( 1 << Bit ); }
    static void unset() { *Port[P] &= ~( 1 << Bit ); }
    static void isOutput() { *Direction[P] |= ( 1 << Bit ); }
    static void isInput()  { *Direction[P] &= ~( 1 << Bit ); }
};

#endif
