#define F_CPU 1000000L      

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

int main(void)
{

    DDRA=0xff;

    while(1) {
        PORTA = 0xff;
        _delay_ms(500);
        PORTA = 0;
        _delay_ms(500);
    }

    return 0;
}
