#define F_CPU 1000000L      

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

static uint8_t digits[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 
        0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};

inline uint8_t debounce()
{
    if ( !(PINB & 1) )
    {
        _delay_ms(20);  
        if ( !(PINB & 1) )
        {
            //_delay_ms(100);  
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    DDRA=0xff;
    DDRB &= 0xfe;
    PORTB |= 1;
    
    uint8_t i;
    uint8_t last = 0;
    uint8_t count = 0;
    while(1){
        if (debounce()) {
            if (!last) {
                count ++;
                count %= 10;
                PORTA= digits[count];
            }
            last = 1;
        } else {
            last = 0;
        }
        /*
        for(i=0;i<10;i++){
            PORTA = digits[i];
            _delay_ms(1000);
        }
        */
    }

    return 0;
}
