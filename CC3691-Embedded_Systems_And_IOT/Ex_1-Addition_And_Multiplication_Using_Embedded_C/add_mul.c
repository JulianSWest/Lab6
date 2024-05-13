#include <reg51.h>

void main()
{
    unsigned char a, b;
    unsigned int mult_result;

    a = 10;
    b = 20;

    P0 = a + b;

    mult_result = (unsigned int)a * (unsigned int)b;

    P1 = mult_result & 0x00FF;
    P2 = (mult_result & 0xFF00) >> 8;
}
