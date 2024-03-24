#include "pow.hpp"

int get_msb(ap_uint<256> n)
{
  int i = 0;

  while (n > 0) {
#pragma HLS PIPELINE off
    n >>= 1;
    i++;
  }

  /* return -1 if a == 0. */
  return i - 1;
}

ap_uint<256> left2right_binary(const ap_uint<256> a, const ap_uint<256> n, mon para)
{
#pragma HLS ALLOCATION function instances=MR limit=1
	ap_uint<256>  x = 1;
	ap_uint<256> n_temp = n;
	 int i;

	  for (i = get_msb(n); i >= 0; i--) {
	#pragma HLS PIPELINE off
	    x = MR(x,x,para);

	    n_temp>>=1;
	    if (n_temp & 1) {
	      x =  MR(x,a,para);
	    }
	  }

	  return x;
}

ap_uint<256> pow(const ap_uint<256> x, const ap_uint<256> n, const mon para) 
{
#pragma HLS ALLOCATION function instances=MR limit=1
	ap_uint<256>  ret = 1;
	int i;
    for(i=256-1;i>=0;i--){
#pragma HLS PIPELINE OFF
    	ret=MR(ret,ret,para);
    	if(n[i]==1){
    		std::cout<<"1だよ"<<std::endl;
    		ret=MR(ret,x,para);
    	}
    }
    return ret;
}

/*
ap_uint<64> two_k_ary(ap_uint<64> x, ap_uint<64> n) {
	size_t D=3;
	size_t K=1<<D;
	size_t MASK=K-1;
	ap_uint<64> modp = 6641203978126787371;
	ap_uint<64> ret = 1;
	ap_uint<64> table[K];
	ap_uint<64> remaining;

	table[0]=1;
	table[1]=x;
	for(int i=2;i<K;i++){
		table[i]=a*table[i-1];
	}
    while (n > 0) {
        if (n & 1) ret = ret * x % modp;  // n の最下位bitが 1 ならば x^(2^i) をかける
        x = x * x % modp;
        n >>= 1;  // n を1bit 左にずらす
    }
    return ret;
}
*/
