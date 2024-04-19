#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "timer.h"
#include "uart1.h"

#include "../cmake/git_version.h"

#define BAUD 2400
#define T_PER_BIT 3

// #define TICK_FREQ_HZ (F_CPU / 64UL) // 56700 Hz with 3.686400 MHz clock
#define TICKS_PER_T (TIMER_TICK_FREQ_HZ / BAUD / T_PER_BIT)
// #define TMR_RELOAD_1T (256 - TICKS_PER_T)
// #define TMR_RELOAD_2T (256 - 2 * TICKS_PER_T)
// #define TMR_RELOAD_5T (256 - 5 * TICKS_PER_T)
// #define TMR_RELOAD_11T (256 - 11 * TICKS_PER_T)

#define TINBUS_DOMINATE PORTD |= (1 << PORTD1)
#define TINBUS_RELEASE PORTD &= ~(1 << PORTD1)

#define TIMER_1T (1 * TICKS_PER_T)
#define TIMER_3T (3 * TICKS_PER_T)
#define TIMER_6T (6 * TICKS_PER_T)
#define TIMER_12T (12 * TICKS_PER_T)
#define TIMER_WAIT(x)                                                                                                  \
    do {                                                                                                               \
        OCR0A = TCNT0 + x;                                                                                             \
    } while (0)

volatile static uint8_t tx_buffer[8];
volatile static uint8_t *tx_ptr = tx_buffer;

enum {
    RX_ACTIVE = 0,
    TX_READY,
    TX_ENABLE,
    TX_DISABLE,
};

enum {
    SEND_EMPTY = 0,
    SEND_ONE,
    SEND_ZERO,
    SEND_DONE,
};

volatile static uint8_t tinbus_state = RX_ACTIVE;

void tinbus_init(void) {
    tinbus_state = RX_ACTIVE;
    TIMER_WAIT(TIMER_12T);
}

int main(void) {
    tinbus_init();
    sei();
    wdt_enable(WDTO_1S);

    // TCCR2B = (1 << CS22); // divide F_CPU by 64
    // TIMSK2 = (1 << OCIE2A);
    TIMSK0 = (1 << OCIE0A);

    DDRD |= (1 << PORTD1);

    stdout = uart1_device;
    stdin = uart1_device;

    while (1) {
        wdt_reset();

        puts(git_version);
        printf("F_CPU %ld\n", F_CPU);

        // tx_buffer[0] = TX_PULSE;
        // tx_buffer[1] = TX_ONE_BREAK;
        // tx_buffer[2] = TX_PULSE;
        // tx_buffer[3] = TX_ZERO_BREAK;
        // tx_buffer[4] = TX_PULSE;
        // tx_buffer[5] = TX_MESSAGE_BREAK;
        // tx_buffer[6] = TX_PULSE;
        // tx_buffer[7] = TX_IDLE;

        // tx_ptr = tx_buffer;

        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
        _delay_ms(100);
    }
}

ISR(TIMER0_COMPA_vect) {
    static uint8_t tx_data;

    switch (tinbus_state) {
    case RX_ACTIVE:
        tinbus_state = TX_READY;
        break;

    case TX_READY:
        tinbus_state = TX_READY;
        break;

    case TX_ENABLE:
        TINBUS_DOMINATE;
        TIMER_WAIT(TIMER_1T);
        tinbus_state = TX_DISABLE;

    case TX_DISABLE: {
        TINBUS_RELEASE;
        if ((tx_data & 0x03) == SEND_EMPTY) {
            tx_data = *tx_ptr++;
        }
        if ((tx_data & 0x03) == SEND_ONE) {
            TIMER_WAIT(TIMER_6T);
            tinbus_state = TX_ENABLE;
        } else if ((tx_data & 0x03) == SEND_ZERO) {
            TIMER_WAIT(TIMER_3T);
            tinbus_state = TX_ENABLE;
        } else if ((tx_data & 0x03) == SEND_DONE) {
            tinbus_state = RX_ACTIVE;
        }
        tx_data >>= 2;
        break;
    }

    default:
        tinbus_state = TX_READY;
        break;
    }

    if (tinbus_state == RX_ACTIVE) {
        tinbus_state = TX_READY;
    } else if (tinbus_state == TX_READY) {

    } else if (tinbus_state == TX_ENABLE) {
        TINBUS_DOMINATE;
        TIMER_WAIT(TIMER_1T);
        tinbus_state = TX_DISABLE;
    } else if (tinbus_state == TX_DISABLE) {
        // PORTD &= ~(1 << PORTD1);
        TINBUS_RELEASE;
        uint8_t data = *tx_ptr;
        if (data == SEND_EMPTY) {
            tx_ptr++;
            data = *tx_ptr;
        }
        tinbus_state = TX_ENABLE;
        tinbus_state = RX_ACTIVE;
    }
}