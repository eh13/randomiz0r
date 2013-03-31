#define F_CPU 1000000L      

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/eeprom.h>
//#include "/usr/avr/include/avr/iotn24a.h"

static uint8_t digits[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 
        0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};

uint8_t ee_range EEMEM;
uint8_t range;

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

void edit()
{
    uint8_t last = 0;
    uint16_t count_push = 0;
    uint16_t count_point = 0; 

    PORTA = digits[range];
    while(1){
	count_point++;
	if (count_point>12){
	    count_point = 0;
	    PORTA ^= 0x80;
	}
        if (debounce()) {
            if (!last) {
                count_push = 0;
            } else {
                count_push++;
            }
            last = 1;
        } else {
            if (last){
                if (count_push>79){
                    PORTA |= 0x80;
		    eeprom_write_byte(&ee_range,range);
		    return;
                } else {
                    range++;
		    if (range>9){
			range = 1;
		    }
		    PORTA |= 0x7f;
		    PORTA &= digits[range];
                }
            }
            last = 0;
	    _delay_ms(20);
        }
    }

}

void roll()
{
    uint8_t i;
    for (i=0;i<3;i++){
	PORTA = 0b11111110;
	_delay_ms(50);
    	PORTA = 0b11011111;
    	_delay_ms(50);
    	PORTA = 0b10111111;
    	_delay_ms(50);
    	PORTA = 0b11111011;
    	_delay_ms(50);
    	PORTA = 0b11110111;
    	_delay_ms(50);
    	PORTA = 0b11101111;
    	_delay_ms(50);
    	PORTA = 0b10111111;
    	_delay_ms(50);
    	PORTA = 0b11111101;
    	_delay_ms(50);
    }
    PORTA = digits[TCNT0 % (range+1)];
}

int main(void)
{
    DDRA=0xff;
    DDRB &= 0xfe;
    PORTB |= 1;
    
    uint8_t last = 0;
    uint16_t count = 0;

    TCCR0B &= 0xf8;
    TCCR0B |= 0x01;

    uint8_t ee_value = eeprom_read_byte (&ee_range);
    if ((ee_value==0) || (ee_value>9)){
	range = 1;
    } else {
	range = ee_value;
    }

    PORTA = 0xff;
    while(1){
        if (debounce()) {
            if (!last) {
                count = 0;
            } else {
		count++;
	    }
            last = 1;
        } else {
	    if (last){
		if (count>79){
		    edit();
		} else {
		    roll();
		}
	    }
            last = 0;
        }
    }

    return 0;
}

/*
hochzaehlen
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
*/
