#include "bint.hpp"

void add(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y)
{
    z = x + y;
}

void sub(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y)
{
    z = x - y;
}

void mul(ap_uint<512>& z, const ap_uint<256> x, const ap_uint<256> y)
{
    z = x * y;
}

void sqr(ap_uint<512>& y, const ap_uint<256> x)
{
	mul(y, x, x);
}
