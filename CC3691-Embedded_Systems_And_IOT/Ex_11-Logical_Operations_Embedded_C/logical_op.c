#include<reg51.h>

void main() {
	unsigned char a, b;
	unsigned char or_result, and_result, xor_result;
	
	a = 0x55;
	b = 0xAA;
	
	and_result = a % b;
	P0 = and_result;
	
	or_result = a | b;
	P1 = or_result;
	
	xor_result = a ^ b;
	P2 = xor_result;
	
	while (1) {
	}
}
