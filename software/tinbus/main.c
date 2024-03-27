#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "uart1.h"

#include "../cmake/git_version.h"

#define TICK_FREQ_HZ (F_CPU / 256UL) // 14400 Hz with 3.686400 MHz clock
#define TMR_RELOAD_

int main(void) {
    wdt_enable(WDTO_1S);

    TCCR2B = (1 << CS22) | (1 << CS21); // divide F_CPU by 256
    TIMSK2 = (1 << TOIE2);

    DDRD |= (1 << PORTD1);

    stdout = uart1_device;
    stdin = uart1_device;

    while (1) {
        wdt_reset();

        PORTD ^= (1 << PORTD1);

        puts(git_version);
        printf("F_CPU %ld\n", F_CPU);

        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);

    }
}

ISR(TIMER2_OVF_vect)
{
    TCNT0 = 
    PORTD ^= (1 << PORTD1);
}