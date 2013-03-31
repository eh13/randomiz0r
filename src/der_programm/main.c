#define F_CPU 1000000L      

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

static uint8_t digits[10] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,
                             0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};

int main(void)
{

    DDRA=0xff;
    uint8_t i;
    while(1){
	for(i=0;i<10;i++){
		PORTA = digits[i];
		_delay_ms(1000);
	}
    }

    return 0;
}
