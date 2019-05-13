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
	printf("addition test pass! \n");

	// test subtraction
	sub_256bit(a, b);
	assert(a[7] == 2);
	printf("subtraction test pass! \n");

	// test addition with 32-bit number
	add_256bit_32bit(a, 16);
	assert(a[7] == 2);
	assert(a[0] == 16);
	printf("32-bit addition test pass! \n");

	// test right shift
	right_shift_256bit(a, 3);
	assert(a[6] == 0x40000000);
	assert(a[0] == 2);
	printf("right shif test pass! \n");

	// test left shift
	left_shift_256bit(a, 3);
	assert(a[7] == 2);
	assert(a[0] == 16);
	printf("left shift test pass! \n");

	//test bits
	assert(bits(a) == 225);
	a[7] = 0;
	assert(bits(a) == 4);
	printf("bits test pass! \n");

	// test multiplication
	multiply_256bit(a, 0xffffffff);
	assert(a[0] == 0xfffffff0);
	assert(a[1] == 0x0000000f);
	printf("multiplication test pass! \n");

	// test divide
	memset(a, 0, BYTES_256bits);
	a[7] = 2;
	a[0] = 5;
	memset(b, 0, BYTES_256bits);
	b[0] = 4;
	divide_256bit(a, b);
	assert(a[0] == 1 && a[6] == 0x80000000);
	printf("divide test pass! \n");

	printf("All tests pass! \n");

}