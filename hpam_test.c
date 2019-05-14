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
	a[0] = 8;
	memset(b, 0, BYTES_256bits);
	b[0] = 4;
	divide_256bit(a, b);
	print_256bit(a);
	assert(a[0] == 2);
	printf("divide test pass! \n");

	//test hpam
	uint32_t nonce = 2523332608;
	uint32_t hpam_tar[8] = {0}; //store hpam target
	uint32_t normal_target[8] = {0};
	normal_target[7] = 0x000009de;
	normal_target[6] = 0xbb000000;
	printf("normal_target = \n");
	print_256bit(normal_target);
	hpam_target(hpam_tar, nonce, normal_target);
	printf("hpam_tar:\n");
	print_256bit(hpam_tar);
	assert(hpam_tar[0] == 0x984dc5ab && hpam_tar[1] == 0x26e2d5df);
	printf("hpam target test pass! \n");
	printf("All tests pass! \n");

}