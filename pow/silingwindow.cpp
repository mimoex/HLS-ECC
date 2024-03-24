#include "pow.hpp"


ap_uint<256> MR(const ap_uint<256> a, const ap_uint<256> b, const mon& para)
{
#pragma HLS ALLOCATION operation instances=mul limit=1
#pragma HLS PIPELINE off
	ap_uint<512> t;
	ap_uint<256> c;
	ap_uint<256> res;
	t=a*b;

  c =t & para.R;
	c *= para.nr;
	
	//c=c(256,511);
	c *= para.modp;
	c += t;
	//std::cout<<"mae:"<<std::endl;
	//std::cout<<c<<std::endl;
	c >>= para.nbit;
	//res=c(256,511);
	//std::cout<<c<<std::endl;

	if (res >= para.modp) res -= para.modp;
	return res;
}

/*
struct windows {
  struct window {
	  ap_uint<1> one;		//1 or 0が入る
	  ap_uint<2> length;	//1~3が入る
  } window[320];
  int length;
};

void decompose_bits(ap_uint<256> n, struct windows *windows)
{
  int j;
  ap_uint<1> one;
  int i = get_msb(n) - 1;

  windows->length = 0;

  while (i >= 0) {
    one = (n >> i) & 1;

    for (j = 1; j < D && i >= j && one == ((n >> (i - j)) & 1); j++) {
#pragma HLS PIPELINE off
    }

    windows->window[windows->length].one = one;
    windows->window[windows->length].length = j;
    windows->length++;


    i -= j;
  }
}

ap_uint<256> sliding_window(ap_uint<256> a, ap_uint<256> n, mon para)
{

#pragma HLS ALLOCATION function instances=MR limit=1
	ap_uint<256> x = 1, aa;
	aa= MR(a,a,para);
  int i, j;
  ap_uint<256> table[D + 1];
  struct windows windows;

  table[0] = a;

  for (i = 1; i < D + 1; i++) {
#pragma HLS PIPELINE off

    //table[i] = aa * table[i - 1]%modp;
    table[i] = MR(aa,table[i - 1],para);
  }

  decompose_bits(n, &windows);

int test=0;

  for (i = 0; i < windows.length; i++) {
    for (j = 0; j < windows.window[i].length; j++) {
#pragma HLS PIPELINE off
      //x = x*x%modp;
    	x = MR(x,x,para);
    	std::cout<<test++<<std::endl;
    }

    if (windows.window[i].one) {


      j = (1 << (windows.window[i].length - 1)) - 1;
      //x = x*table[j]%modp;
      x = MR(x,table[j],para);
      std::cout<<test++<<std::endl;
    }
  }

  return x;
}

*/

int max(const int a, const int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}


#define D 2


ap_uint<256> sliding_window(const ap_uint<256> x, const ap_uint<256> y, mon para)
{
#pragma HLS PIPELINE off
    ap_uint<256> table[1<<D] = {0}; // k+1要素のテーブル
    ap_uint<256> aa;
    table[1] = x;
    //ap_uint<256> aa = (base * base) % para.modp;
    aa=MR(x,x,para);
        for (int i = 1; i < (1 << (D - 1)); i++) {
#pragma HLS PIPELINE off
        table[2*i+1] = MR(table[2*i-1],aa,para);
        std::cout<<"table: "<<table[2*i+1]<<std::endl;
    }

    ap_uint<256> result = 1;
    int length = 256;

    // print binary y
    for(int i=0; i<length; ++i){
#pragma HLS PIPELINE off
      std::cout<<y[i];
    }
    std::cout<<std::endl;

    int i = length - 1;
    while(i >= 0) {
#pragma HLS PIPELINE off
        //if (((bin_exp >> i) & 1) == 0) {
          if(y[i]==0){
            std::cout<<"0"<<std::endl;
            result = MR(result,result,para);
            i--;
        } else {
            int s = max(0, i - D + 1);
            //while (((bin_exp >> s) & 1) == 0) {
              while(y[s]==0){
#pragma HLS PIPELINE off
                s++;
            }
            for(int j=0; j<i-s+1; ++j){
#pragma HLS PIPELINE off
              result = MR(result,result,para);
            }

            ap_uint<D> window_bits = y(s,i);
            std::cout<<y(s,i)<<std::endl;
            result = MR(result,table[window_bits],para);
            i = s - 1;
        }
    }
}

    return result;
}
