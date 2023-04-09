#include <iostream>
#include "ap_int.h"

struct Point {
	ap_uint<256> X,Z;
};

struct mon {
	const ap_uint<256> mod;
	const size_t nbit;
	const ap_uint<256> R;
	const ap_uint<256> R2;
	const ap_uint<256> nr;
	const ap_uint<256> R2mon;
	const ap_uint<256> inv4;
};

extern mon para;

//—LŒÀ‘Ì‚Ì‰ÁZ	c=a+b %p
void add_fp( ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);
//—LŒÀ‘Ì‚ÌŒ¸Z	c=a-b %p
void sub_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);
//—LŒÀ‘Ì‚ÌæZ	c=a*b %p
void mul_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);
void mul_mon(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);
void pow_mon(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);
void div_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b);

void MR(const ap_uint<512>& t, ap_uint<256>* z);

Point xMUL(const ap_uint<256>& n);
