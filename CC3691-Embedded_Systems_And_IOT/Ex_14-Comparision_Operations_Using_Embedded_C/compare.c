#include <reg51.h>

void main()
{
    unsigned char a, b;

    a = 10;
    b = 20;

    if (a < b)
    {
        P0 = 0xFF;
    }
    else
    {
        P0 = 0x00;
    }

    if (a == b)
    {
        P1 = 0xFF;
    }
    else
    {
        P1 = 0x00;
    }

    if (a > b)
    {
        P2 = 0xFF;
    }
    else
    {
        P2 = 0x00;
    }

    while(1)
    {
    }
}
