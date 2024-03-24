#include "pow.hpp"

ap_uint<256> amari(ap_uint<256> x, ap_uint<256> y, mon para)
{
#pragma HLS INTERFACE mode=s_axilite port=y
#pragma HLS INTERFACE mode=s_axilite port=x
#pragma HLS INTERFACE mode=s_axilite port=para
	ap_uint<256> ret;
	ap_uint<512> temp;
#pragma HLS INTERFACE mode=s_axilite port=return
	temp=x*y;
	ret=temp%para.modp;
	return ret;
}

ap_uint<256> addMod(const ap_uint<256> x, const ap_uint<256> y, mon para)
{
	ap_uint<256> temp;
	temp= x+ y;
	if (temp >= para.modp) temp-= para.modp;
	return temp;
}

ap_uint<256> addModSlow(const ap_uint<256> x, const ap_uint<256> y, mon para)
{
	ap_uint<256> temp;
	temp= x+ y;
	temp=temp%para.modp;
	return temp;
}
