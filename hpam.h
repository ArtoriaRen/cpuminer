void hpam_target(uint32_t hpam_tar[],const uint32_t nonce,const uint32_t* ptarget);
//in-place addition
void add_256bit(uint32_t a[], uint32_t b);
//in-place addition
void add_256bit(uint32_t a[], uint32_t b);
// in-place multiplication
void multiply_256bit(uint32_t a[], uint32_t b);
//in-place division
void divide_256bit(uint32_t a[], uint32_t b[]);
// find the first non-zero bit
int bits(uint32_t a[]);
//in-place left shift
void left_shift_256bit(uint32_t a[], unsigned int shift);
//in-place right shift
void right_shift_256bit(uint32_t a[], unsigned int shift);
