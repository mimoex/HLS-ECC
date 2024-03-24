#include "fp.hpp"

//Montgomery multiplicatuon
mon para = {
	ap_uint<256>("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f"),
	256,
	ap_uint<256>("115792089237316195423570985008687907853269984665640564039457584007913129639935"),
	ap_uint<256>("18446752466076602529"),
	ap_uint<256>("91248989341183975618893650062416139444822672217621753343178995607987479196977"),
	ap_uint<256>("4294968273")
};

void add_fp(ap_uint<256>& c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> temp;
	temp = a + b;
	if (temp >= para.modp) temp -= para.modp;
	c = temp;
}

void sub_fp(ap_uint<256>& c, const ap_uint<256> &a, const ap_uint<256> &b)
{
	if (a >= b) c = a - b;
	else c = a + para.modp - b;
}

void mul_fp(ap_uint<256> &c, const ap_uint<256>& a, const ap_uint<256>& b)
{
//#pragma HLS INLINE
#pragma HLS ALLOCATION operation instances=mul limit=1
#pragma HLS PIPELINE off

	ap_uint<512> t;
	ap_uint<512> temp;
	ap_uint<256> res;
	t=a * b;

	temp = t & para.R;
	temp *= para.nr;

	//c=c(256,511);
	temp *= para.modp;
	temp += t;
	//std::cout<<"mae:"<<std::endl;
	//std::cout<<c<<std::endl;
	//temp >>= para.nbit;
	res=temp(256,511);
	//std::cout<<c<<std::endl;

	if (res >= para.modp) res -= para.modp;
	c=res;
}

void pow_mon(ap_uint<256> &c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> result;

	result=para.R2mon;

	//std::cout<<b<<std::ends;

    BinaryMethod : for (int i = para.nbit - 1; i >=0; i--) {
#pragma HLS PIPELINE off
    	//std::cout<<b[i]<<std::ends;
    	mul_fp(result, result, result);

		if (b[i] == 1) mul_fp(result, a, result);
    }
    c=result;
}

// p-2 inv
/*
void inv_fp(ap_uint<256>* c, const ap_uint<256> a)
{
	if (a == 0) {
		//throw std::range_error("Divided by zero.");
		c=0;
	}
	else {
		pow_mon(c, a, para.modp - 2);
	}
}
*/
void inv_fp(ap_uint<256>* c, const ap_uint<256>& a)
{
#pragma HLS PIPELINE off
	ap_uint<256> u,v,r,s;
	u=para.modp;
	v=a;
	r=0;
	s=1;

	for(int i=255;i>=0;i--){
				std::cout<<v[i];
			}
			std::cout<<std::endl;

	while(u!=1 && v!=1){
		while((u[0]) ==0){
			u>>=1;
			if((r[0])==1)
				r+=para.modp;
			r>>=1;
		}
		while((v[0])==0){
			v>>=1;
			if((s[0])==1)
				s+=para.modp;
			s>>=1;
		}
		if(u>=v){
			u-=v;
			r-=s;
			if(r>=s)
				r+=para.modp;
		} else {
			v-=u;
			s-=r;
			if(s>=r)
				s+=para.modp;
		}
	}
	if(u==1)
		sub_fp(*c,r,para.modp);
	else{
		sub_fp(*c,s,para.modp);
	}
	ap_uint<256> test;
	sub_fp(test,r,para.modp);
	std::cout<< test<<std::endl;
}

void div_fp(ap_uint<256>& c, const ap_uint<256>& a, const ap_uint<256>& b)
{
#pragma HLS INLINE OFF
//#pragma HLS PIPELINE off
#pragma HLS ALLOCATION function instances=mul_fp limit=1
	ap_uint<256> yinv, y, ytemp;
	//mul_fp(y, b,1);
	y=b;
	inv_fp(&yinv,y);
	mul_fp(c,a,yinv);
	std::cout<<"test:"<<c<<std::endl;
	//mul_fp(ytemp, yinv, para.R2);

	//mul_fp(c, a,ytemp);

}

/*
void div_fp(ap_uint<256>* c, const ap_uint<256>& a, const ap_uint<256>& b)
{
	ap_uint<256> tempmon;
	ap_uint<256> amon, bmon;

	//MR(a * para.R2, &amon);
	//MR(b * para.R2, &bmon);
	inv_fp(&tempmon, bmon);
	mul_fp(&tempmon, amon, tempmon);
	//MR256(tempmon,&tempmon);
	*c=tempmon;
}
*/
