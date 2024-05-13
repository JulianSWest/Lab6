#include<reg51.h>

void main() {
	unsigned char a, b;
	unsigned char sub_result;
	unsigned char div_result;
	unsigned char remainder;
	
	a = 100;
	b = 20;
	
	sub_result = a - b;
	P0 = sub_result;
	
	if (b != 0) {
		div_result = a / b;
		remainder = a % b;
	}
	else {
		div_result = 0;
		remainder = 0;
	}
	
	P1 = div_result;
	P2 = remainder;
}
