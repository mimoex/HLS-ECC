#include <iostream>
#include "ap_int.h"

struct Point {
	ap_uint<256> X,Y,Z;
	bool isZero = false;
};

struct mon {
	const ap_uint<256> modp;
	const size_t nbit;
	const ap_uint<256> R;
	const ap_uint<256> R2;
	const ap_uint<256> nr;
	const ap_uint<256> R2mon; // 1Z
};

extern mon para;

//有限体の加算	c=a+b %p
void add_fp(ap_uint<256>& c, const ap_uint<256>& a, const ap_uint<256>& b);
//有限体の減算	c=a-b %p
void sub_fp(ap_uint<256>& c, const ap_uint<256> &a, const ap_uint<256> &b);
//有限体の乗算	c=a*b %p
void mul_fp(ap_uint<256> &c, const ap_uint<256>& a, const ap_uint<256>& b);
void pow_mon(ap_uint<256> &c, const ap_uint<256>& a, const ap_uint<256>& b);
void div_fp(ap_uint<256>& c, const ap_uint<256>& a, const ap_uint<256>& b);

Point xMUL();
