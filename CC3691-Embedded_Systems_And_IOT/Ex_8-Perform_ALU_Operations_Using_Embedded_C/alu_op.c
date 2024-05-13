#include<reg51.h>

void main() {
	unsigned char a, b;
	a = 200;
	b = 100;
	P0 = a + b;
	P1 = a - b;
	P2 = a/b;
	P3 = a%b;
}
