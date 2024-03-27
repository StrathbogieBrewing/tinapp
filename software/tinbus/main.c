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

#define BAUD 2400
#define T_PER_BIT 3

#define TICK_FREQ_HZ (F_CPU / 64UL) // 56700 Hz with 3.686400 MHz clock
#define TICKS_PER_T (TICK_FREQ_HZ / BAUD / T_PER_BIT)
// #define TMR_RELOAD_1T (256 - TICKS_PER_T)
// #define TMR_RELOAD_2T (256 - 2 * TICKS_PER_T)
// #define TMR_RELOAD_5T (256 - 5 * TICKS_PER_T)
// #define TMR_RELOAD_11T (256 - 11 * TICKS_PER_T)

volatile static uint8_t tx_buffer[8];
volatile static uint8_t *tx_ptr = tx_buffer;

enum {
    TX_IDLE = 0,
    TX_PULSE,
    TX_ONE_BREAK,
    TX_ZERO_BREAK,
    TX_MESSAGE_BREAK,
};

int main(void) {
    sei();
    wdt_enable(WDTO_1S);

    TCCR2B = (1 << CS22); // divide F_CPU by 64
    TIMSK2 = (1 << OCIE2A);

    DDRD |= (1 << PORTD1);

    stdout = uart1_device;
    stdin = uart1_device;

    while (1) {
        wdt_reset();

        puts(git_version);
        printf("F_CPU %ld\n", F_CPU);

        tx_buffer[0] = TX_PULSE;
        tx_buffer[1] = TX_ONE_BREAK;
        tx_buffer[2] = TX_PULSE;
        tx_buffer[3] = TX_ZERO_BREAK;
        tx_buffer[4] = TX_PULSE;
        tx_buffer[5] = TX_MESSAGE_BREAK;
        tx_buffer[6] = TX_PULSE;
        tx_buffer[7] = TX_IDLE;

        tx_ptr = tx_buffer;

        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
    }
}

ISR(TIMER2_COMPA_vect) {
    // PORTD ^= (1 << PORTD1);
    uint8_t tx_control = *tx_ptr;
    if (tx_control == TX_PULSE) {
        PORTD |= (1 << PORTD1);
        OCR2A += TICKS_PER_T;
    } else {
        PORTD &= ~(1 << PORTD1);
        if (tx_control == TX_ZERO_BREAK) {
            OCR2A += 2 * TICKS_PER_T;
        } else if (tx_control == TX_ONE_BREAK) {
            OCR2A += 5 * TICKS_PER_T;
        } else if (tx_control == TX_MESSAGE_BREAK) {
            OCR2A += 11 * TICKS_PER_T;
        }
    }
    if (tx_control != TX_IDLE) {
        tx_ptr++;
    }
}