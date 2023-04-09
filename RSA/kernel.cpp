#include "kernel.hpp"

#define R 0x10000000000000000000000000000000000000000000000000000000000000000
#define RIND 256

ap_uint<256> n_dash(const ap_uint<256> n){
  ap_uint<512> result = 0;
  ap_uint<512> t = 0;
  ap_uint<512> r ;

  ap_uint<512> i = 1;
  ap_uint<512> cn = n;
  ap_uint<256> r_dash;


  r = 1;
  r = r << RIND;

  for (int ii = 0; ii < RIND; ++ii)
  {
#pragma HLS UNROLL factor=2
    if( !( t % 2 ) )
    {
      t += cn;
      result += i;
    }
    t /= 2;
    r /= 2;
    i *= 2;

  }
  r_dash = result;
  return(r_dash);
}


//MontgomeryReduction
ap_uint<512> MR(const ap_uint<512> x,const ap_uint<256> N,const ap_uint<256> NINV){
  ap_uint<1024> rconst = 1;
  rconst = rconst << RIND;
  rconst = rconst - 1;

  ap_uint<1024> mninv = NINV;
  ap_uint<1024> mn = N;
  ap_uint<1024> mx = x;
  ap_uint<1024> xninv;
  ap_uint<1024> xninvr;
  ap_uint<1024> xninvrn;
  ap_uint<1024> xxninvrn;
  ap_uint<1024> ret;
  ap_uint<512> ret512;

//   return (x + (x * NINV & rconst) * N) >> RIND;
  xninv = mx * mninv;
  xninvr = xninv & rconst;
  xninvrn = xninvr * mn;
  xxninvrn = mx + xninvrn;
  ret = xxninvrn >> RIND;
  if(ret > mn){
    ret = ret - mn;
  }
  ret512 = ret;

  return (ret512);
}


void kernel(
  ap_uint<128> plain,
  ap_uint<128> e,
  ap_uint<256> n,
  ap_uint<256>* encrypted
) {

  // *encrypted = (plain ^ e) % n

  int  ii;

  ap_uint<256>  NINV;
  ap_uint<512>  en = 1;
  ap_uint<512>  A;
  ap_uint<512>  ONE;
  ap_uint<512>  cp = plain;
  ap_uint<512>  c;
  ap_uint<512>  NN;
  ap_uint<514>  r2m;
  ap_uint<514>  nm;
  ap_uint<512>  r2;
  ap_uint<512>  ans_en ;

  nm = n;
  r2m = 1;
  r2m = r2m << RIND;
  r2m = r2m * r2m;
//  r2m = r2m % nm;
  for (int jj = 257; jj >= 0; jj--)
  {
#pragma HLS UNROLL factor=2
    ap_uint<514> jj_u = jj;
    ap_uint<514> div;
    div = nm << jj_u;
    if(r2m > div){
      r2m = r2m - div;
    }
  }
  r2 = r2m;

  NINV = n_dash(n);
  cp = cp * r2;
  A = MR(cp ,n,NINV);
  en = en * r2;
  en = ONE = MR(en,n,NINV);

  for (ii = 127; ii >= 0; ii--)
  {
    ap_uint<128>  chk = 1;
    ap_uint<128>  ci = ii;
    chk = chk << ii;
    if((e & chk) != 0){
      c = A;
    } else {
      c = ONE;
    }
    en = en * en;
    en = MR(en,n,NINV);
    en = en * c;
    en = MR(en,n,NINV);
  }
  en = MR(en,n,NINV);
  *encrypted = en;
}
