#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include "hpam.h"

int main(){
	uint32_t a[8] = {0}, b[8] ={0};
	a[7] = 2;
	b[7] = 1;

	// test addition
	add_256bit(a, b);
	assert(a[7] == 3);

	// test subtraction
	sub_256bit(a, b);
	assert(a[7] == 2);

	// test addition with 32-bit number
	add_256bit_32bit(a, 16);
	assert(a[7] == 2);
	assert(a[0] == 16);

	// test right shift
	right_shift_256bit(a, 3);
	assert(a[6] == 0x40000000);
	assert(a[0] == 2);

	// test left shift
	left_shift_256bit(a, 3);
	assert(a[7] == 2);
	assert(a[0] == 16);

	//test bits
	// printf("bits(a) = %d \n", bits(a));
	assert(bits(a) == 225);
	a[7] = 0;
	assert(bits(a) == 4);

	// test multiplication
	multiply_256bit(a, 0xffffffff);
	assert(a[0] == 0xfffffff0);
	assert(a[1] == 0x0000000f);



}