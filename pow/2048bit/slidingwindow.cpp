#include "pow.hpp"

uint2048_t mul_fp(const uint2048_t a, const uint2048_t b, const mon& para)
{
#pragma HLS allocation function instances=mul limit=1
#pragma HLS PIPELINE off

#pragma HLS inline off
	uint4096_t c4, t;
	uint2048_t c2;
	mul(t,a,b);
	//c2 = (t & para.R);
	//c2=t(2048,4095);
	for(int i=0;i<8;i++){
		c2.buf[i]=t.buf[i+4];
	}

	//c4 = c2*para.nr;
	mul(c4,c2,para.nr);

	//c2 = c4&para.R;
	//c2=c4(2048,4095);
	for(int i=0;i<8;i++){
		c2.buf[i]=c4.buf[i+4];
	}
	//c4 = c2*para.modp;
	mul(c4,c2,para.modp);
	//c4 += t;
	addT(c4.buf,c4.buf,t.buf);

	//c2 = c4>>para.nbit;
	shrT(c2.buf, c4.buf, 256);

	//if (c2 >= para.modp) c2 -= para.modp;
	if (cmpGeT(c2.buf, para.modp.buf)){
		subT(c2.buf,c2.buf,para.modp.buf);
	}
	return c2;
}

void binary(uint2048_t z, const uint2048_t x, const uint2048_t y, mon para)
{
#pragma HLS PIPELINE OFF
	uint2048_t result, temp;
    temp = x;
	    result.buf[0]= 1;
	    result.buf[1]=0;
	    result.buf[2]=0;
	    result.buf[3]=0;
	    result.buf[4]=0;
	    result.buf[5]=0;
	    result.buf[6]=0;
	    result.buf[7]=0;
	    std::cout<<"xxxxx= "<<result.buf[1]<<std::endl;
	    int length = 256;

		for(int kk=0;kk<8;kk++){
#pragma HLS PIPELINE OFF
            for(int i=256-1;i>=0;i--){
             #pragma HLS PIPELINE OFF
                if(y.buf[kk][i]==1){
                    result = mul_fp(result,temp,para);
                }
                temp = mul_fp(temp,temp,para);
            }
		}
        z = result;
}

int max(const int a, const int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

#define D 3

uint2048_t sliding_window(const uint2048_t x, const uint2048_t y, mon para)
{
#pragma HLS PIPELINE off
    uint2048_t table[1<<D] = {0}; // k+1要素のテーブル
    uint2048_t aa;
    //table[1] = x;
    copyT(table[1],x);
    //ap_uint<256> aa = (base * base) % para.modp;
    aa=mul_fp(x,x,para);
        for (int i = 1; i < (1 << (D - 1)); i++) {
#pragma HLS PIPELINE off
        table[2*i+1] = mul_fp(table[2*i-1],aa,para);
    }

    uint2048_t result;
    result.buf[0]= 1;

	for(int kk=0;kk<8;kk++){
#pragma HLS PIPELINE off
		int i = 255; //256 - 1;
		while(i >= 0) {
#pragma HLS PIPELINE off
			//if (((bin_exp >> i) & 1) == 0) {
			if(y.buf[kk][i]==0){
				std::cout<<"0"<<std::endl;
				result = mul_fp(result,result,para);
				i--;
			} else {
				int s = max(0, i - D + 1);
				//while (((bin_exp >> s) & 1) == 0) {
				while(y.buf[kk][s]==0){
#pragma HLS PIPELINE off
					s++;
				}
				for(int j=0; j<i-s+1; ++j){
#pragma HLS PIPELINE off
					result = mul_fp(result,result,para);
				}

            ap_uint<D> window_bits = y.buf[kk](s,i);
            std::cout<<y.buf[kk](s,i)<<std::endl;
            result = mul_fp(result,table[window_bits],para);
            i = s - 1;
        }
    }
    }
    return result;
}
