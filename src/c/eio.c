#include "eio.h"
#include "types.h"

char digitToChar(u32 digit) {
	char x = digit + '0';
	return x;
}

void numberToString(char* buf, u32 number) {
	if (number < 1) { // doesn't support negative numbers
		buf[0] = '0';
	}
	int idx = 0;
	int digits = 1;
	while (digits*10 < number) {
		//buf[digits-1] = digitToChar(number/(digits*10));
		digits++;
	}
	digits -= 3;
	while (idx < digits) {
		u32 digit = 0;
		if (idx > 0) {
			digit = number / (idx*10) % 10;
		} else {
			digit = number % 10;
		}
		buf[digits-idx-1] = digitToChar(digit);
		idx++;
	}
}