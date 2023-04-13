#include "bint.hpp"
#include "fp.hpp"

//Montgomery multiplicatuon
mon para = {
	ap_uint<256>("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed"),
	255,
	ap_uint<256>("57896044618658097711785492504343953926634992332820282019728792003956564819967"),
	361,
	ap_uint<256>("21330121701610878104342023554231983025602365596302209165163239159352418617883"),
	19,
	ap_uint<256>("43422033463993573283839119378257965444976244249615211514796594002967423614962")
};

void addMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y)
{
	ap_uint<256> temp;
	add(temp, x, y);
	if (temp >= para.mod) sub(temp, temp, para.mod);
	z = temp;
}

void subMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y)
{
	if (x >= y) {
		sub(z, x, y);
	}
	else {
		ap_uint<256> temp;
		add(temp, x, para.mod);
		sub(z, temp, y);
	}
}

void mulMont(ap_uint<256>& z, const ap_uint<512> x)
{
	ap_uint<512> c512;
	ap_uint<256> c256;
	c256 = (x & para.R);
	//c512 = c256*para.nr;
	mul(c512, c256, para.nr);
	c256 = c512&para.R;
	//c512 = c256*para.mod;
	mul(c512, c256, para.mod);
	//c512 += x;
	add(c512, c512, x);
	c256 = c512>>para.nbit;
	if (c256 >= para.mod) {
		//c256 -= para.mod;
		sub(c256,c256,para.mod);
	}
	z=c256;
}

void mulMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y)
{
//#pragma HLS allocation operation instances=mul limit=1
//#pragma HLS allocation function instances=MR limit=1
	ap_uint<512> xy;
	//temp512=x*y;
	mul(xy, x, y);
	mulMont(z, xy);
}

void sqrMod(ap_uint<256>& z, const ap_uint<256> x)
{
	ap_uint<512> xx;
	sqr(xx,x);
	mulMont(z, xx);
}
