#include "format.h"

void itoa(int val, int format, FILE *stream)
{
    unsigned char digit;
    uint8_t enable_digits = 0;
    // do sign
    if (val < 0)
    {
        val = -val;
        disp.write('-');
    }

    // do 10000's
    digit = '0';
    while (val > 9999)
    {
        val -= 10000;
        digit++;
    }
    if ((digit != '0') || (enable_digits != 0))
    {
        disp.write(digit);
        enable_digits = 1;
    }
    // do 1000's
    digit = '0';
    while (val > 999)
    {
        val -= 1000;
        digit++;
    }
    if ((digit != '0') || (enable_digits != 0))
    {
        disp.write(digit);
        enable_digits = 1;
    }
    // do 100's
    digit = '0';
    while (val > 99)
    {
        val -= 100;
        digit++;
    }
    // if (format == Milli) {
    //   if (enable_digits == 0)
    //     disp.write('0');
    //   disp.write('.');
    //   enable_digits = 1;
    // }
    if ((digit != '0') || (enable_digits != 0))
    {
        disp.write(digit);
        enable_digits = 1;
    }
    // do 10's
    digit = '0';
    while (val > 9)
    {
        val -= 10;
        digit++;
    }
    if (format == Centi)
    {
        if (enable_digits == 0)
            disp.write('0');
        disp.write('.');
        enable_digits = 1;
    }
    if ((digit != '0') || (enable_digits != 0) || (format == TwoDigits))
    {
        disp.write(digit);
        enable_digits = 1;
    }
    // do 1's
    digit = '0' + val;
    if (format == Deci)
    {
        if (enable_digits == 0)
            disp.write('0');
        disp.write('.');
        enable_digits = 1;
    }
    if ((digit != '0') || (enable_digits != 0) || (format == Unit))
    {
        disp.write(digit);
        enable_digits = 1;
    }
}