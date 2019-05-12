#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "hpam.h"

#define BYTES_256bits 32 // 256-bit integer has 32 bytes.

void hpam_target(uint32_t hpam_tar[],const uint32_t nonce,const uint32_t* ptarget){
	unsigned int firstBit = 0;
	int i =0;
	// find the first bit of value 1 in nonce
    for(i = 0; i< 32 && firstBit == 0; i++){
		if((nonce & 1<< (31-i)) != 0){
	    	firstBit = 31 - i;
		}
    }

    // calculate HPAM target
    //hpamTarget = bnTarget/(1 + (bnTarget >> (256 - firstBit))*(nonce >> (firstBit)));//+1 to avoid divided by 0; also convert floor to ceilling.
}

//in-place addition. add a uint32_t number to 256-bit number
void add_256bit(uint32_t a[], uint32_t b){
	uint64_t carry= 0;
	int i=0;

	printf("before adding:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
	
	uint64_t n = b + a[0];
	a[0] = n & 0xffffffff; 
	carry = n >> 32;
	for(i=1; i<8; i++){
		n = carry + a[i];
		  a[i] = n &  0xffffffff;
		carry = n >> 32;
	}

	printf("after adding:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
}

// in-place multiplication
void multiply_256bit(uint32_t a[], uint32_t b){
	uint64_t carry = 0;
	int i=0;
	printf("before multiply :\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
	for(i=0; i<8; i++){
		uint64_t n = carry +(uint64_t)b * a[i];
		a[i] = n &  0xffffffff;
		carry = n >> 32;
	}
	printf("after multiply :\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
}

//in-place division
void divide_256bit(uint32_t a[], uint32_t b[]){
	uint32_t rem[8];
	// make a copy `rem` to store remainder.
	memcpy(rem, a, BYTES_256bits); 
	//clear `a` to store the quotient.
	memset(a, 0, BYTES_256bits);
	int a_bits = bits(a);
	int b_bits = bits(b);
	if(b_bits == 0)
		fprintf(stderr, "division by 0");
	if(b_bits <= a_bits){
		int shift = a_bits - b_bits;
		left_shift_256bit(b, shift);
	
	// while(shift>0){
	// 	if(a>b)
	// 		a 
	// }	
	}

}

// find the first non-zero bit
int bits(uint32_t a[]){
	int i=7, j=31;
	for(; i>=0; i--){
		for(j=31; j>=0; j--){
			if((a[i] & 1<<j) !=0){
				printf("i=%d \n", i);
				return 32*i + j;
			}
		}
	}
	return 0;
}

//in-place left shift
void left_shift_256bit(uint32_t a[], unsigned int shift){
	uint32_t b[8] = {0};
	int i = 0;
	printf("before left shift:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
	//copy a to b
	for(i =0; i<8; i++){
		b[i] = a[i];
	}
	//clear a
	memset(a, 0, BYTES_256bits);
	int k = shift/32;
	shift = shift%32;
	for(i=0; i<8; i++){
		if(i+k+1 < 8 && shift != 0)
			a[i+k+1] |= (b[i] >> (32-shift));
		if(i+k <8)
			a[i+k] |= (b[i] << shift);
	}
	printf("after left shift:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
}

//in-place right shift
void right_shift_256bit(uint32_t a[], unsigned int shift){
	uint32_t b[8] = {0};
	int i = 0;
	printf("before right shift:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
	//copy a to b
	memcpy(b, a, BYTES_256bits);
	//clear a
	memset(a, 0, BYTES_256bits);
	int k = shift/32;
	shift = shift%32;
	for(i=0; i<8; i++){
		if(i-k-1 >=0 && shift != 0){
			// printf("b[%d] = %d\n", i, b[i]);
			a[i-k-1] |= (b[i] << (32-shift));
		}
		if(i-k >= 0)
			a[i-k] |= (b[i] >> shift);
	}
	printf("after right shift:\n");
	for(i=7; i>=0; i--){
		printf("a[%d] = %d, \n", i, a[i]);
	}
}