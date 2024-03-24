#include "fp.hpp"

void mulmod (const ap_uint<256>& a, const ap_uint<256>& b, ap_uint<256> *c)
{
	*c=(a*b)%para.mod;
}

ap_uint<256> MR(const ap_uint<512>& t)
{
	ap_uint<512> c;
	c = (t & para.R) * para.nr;
	c &= para.R;
	c *= para.mod;
	c += t;
	c >>= para.nbit;
	if (c >= para.mod) c -= para.mod;

	return c;
}

void montgomery_mod (const ap_uint<256>& a, const ap_uint<256>& b, ap_uint<256> *c)
{
	ap_uint<512> test;
	test = MR(a * b) * para.R2;
	*c= MR(test);
}
