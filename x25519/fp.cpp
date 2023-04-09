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

void add_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> temp;
	temp = a + b;
	if (temp >= para.mod) temp -= para.mod;
	*c = temp;
}

void sub_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	if (a >= b) *c = a - b;
	else *c = a + para.mod - b;
}

void MR(const ap_uint<512>& t, ap_uint<256>* z)
{
#pragma HLS allocation operation instances=mul limit=1

#pragma HLS inline off
	ap_uint<512> c512;
	ap_uint<256> c256;
	c256 = (t & para.R);
	c512 = c256*para.nr;
	c256 = c512&para.R;
	c512 = c256*para.mod;
	c512 += t;
	c256 = c512>>para.nbit;
	if (c256 >= para.mod) c256 -= para.mod;
	*z=c256;
}


void MR256(const ap_uint<256>& t, ap_uint<256>* z)
{
//#pragma HLS inline off
	ap_uint<512> c512;
	ap_uint<256> c256;
	c512=t;
	MR(c512, &c256);
	*z=c256;
}


void mul_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> temp256;
	ap_uint<512> temp512;
	temp512=a*b;
	MR(temp512,&temp256);
	temp512 = temp256 * para.R2;
	MR(temp512,&temp256);
	*c=temp256;
}

void mul_mon(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
#pragma HLS allocation operation instances=mul limit=1
#pragma HLS allocation function instances=MR limit=1
	ap_uint<512> temp512;

//#pragma HLS BIND_OP variable=temp512 op=mul impl=fabric
	temp512=a*b;
	MR(temp512,c);
}

void pow_mon(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> result;

	result=para.R2mon;

	//std::cout<<b<<std::ends;

    BinaryMethod : for (int i = para.nbit - 1; i >=0; i--) {
#pragma HLS PIPELINE off
    	//std::cout<<b[i]<<std::ends;
    	mul_mon(&result, result, result);

		if (b[i] == 1) mul_mon(&result, a, result);
    }
    *c=result;
}

void inv_fp(ap_uint<256>* c, const ap_uint<256>& a)
{
	if (a == 0) {
		//throw std::range_error("Divided by zero.");
		*c=0;
	}
	else {
		pow_mon(c, a, para.mod - 2);
	}
}


void div_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> tempmon;
	ap_uint<256> amon, bmon;

	MR(a * para.R2, &amon);
	MR(b * para.R2, &bmon);
	inv_fp(&tempmon, bmon);
	mul_mon(&tempmon, amon, tempmon);
	MR256(tempmon,&tempmon);
	*c=tempmon;
}

