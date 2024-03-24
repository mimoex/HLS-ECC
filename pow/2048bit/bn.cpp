#include "pow.hpp"

ap_uint<256> addT(ap_uint<256> z[N], const ap_uint<256> x[N], const ap_uint<256> y[N])
{
	ap_uint<256> c = 0; // 最初は繰り上がりはない
	ap_uint<256> xc;
	ap_uint<256> yi;
  for (size_t i = 0; i < N; i++) {
#pragma HLS PIPELINE off
	  xc  = x[i] + c;
    c = xc < c;
    yi = y[i];
    xc += yi;
    c += xc < yi;
    z[i] = xc;
  }
  return c;
}

ap_uint<256> subT(ap_uint<256> z[N], const ap_uint<256> x[N], const ap_uint<256> y[N])
{
	ap_uint<256> c = 0; // 最初は借り入れがない
    ap_uint<256> yi;
    ap_uint<256> xi;

    for (size_t i = 0; i < N; i++) {
#pragma HLS PIPELINE off
    	yi = y[i];
        yi += c;
        c = yi < c;
        xi = x[i];
        c += xi < yi;
        z[i] = xi - yi;
    }
    return c;
}

uint2048_t copyToUint2048(const uint4096_t& src) {
    uint2048_t dest;
    for (int i = 0; i < N; i++) {
        dest.buf[i] = src.buf[i];
    }
    return dest;
}

uint4096_t copyToUint4096(const uint2048_t& src) {
    uint4096_t dest;
    for (int i = 0; i < N; i++) {
        dest.buf[i] = src.buf[i];
    }
    return dest;
}


ap_uint<256> mulUnitT(ap_uint<256> z[N], const ap_uint<256> x[N], ap_uint<256> y)
{
#pragma HLS pipeline off
	ap_uint<256> H = 0;
    ap_uint<512> v;
  for (size_t i = 0; i < N; i++) {
	  v = x[i]* y;
    v += H;
    z[i] = v;
    H = v >> 256;
  }
  return H; // z[n]
}

/*
ap_uint<256> mulUnitAddT(ap_uint<256> z[N], const ap_uint<256> x[N], ap_uint<256> y)
{
#pragma HLS pipeline off
	ap_uint<256> xy[N], ret;
	ret = mulUnitT(xy, x, y);
	ret += addT(z, z, xy);
	return ret;
}

void mul(uint4096_t& z, const uint2048_t& x, const uint2048_t& y)
{
    uint2048_t z1;
	z.buf[N] = mulUnitT(z.buf, x.buf, y.buf[0]);
	for (size_t i = 1; i < N; i++) {
        #pragma HLS pipeline off
		z.buf[N + i] = mulUnitAddT(&z.buf[i], x.buf, y.buf[i]);

	}
}
*/

void mul(uint4096_t& z, const uint2048_t& x, const uint2048_t& y)
{
    uint2048_t z1;
	z.buf[N] = mulUnitT(z.buf, x.buf, y.buf[0]);
	ap_uint<256> xy[N], ret;
	for (size_t i = 1; i < N; i++) {
        #pragma HLS pipeline off
		//z.buf[N + i] = mulUnitAddT(&z.buf[i], x.buf, y.buf[i]);
		z.buf[N + i] = mulUnitT(xy, x.buf, y.buf[0]);
		//z.buf[N + i] += addT(z.buf, z.buf, xy);
        ap_uint<256> c = 0; // 最初は繰り上がりはない
        ap_uint<256> xc;
        ap_uint<256> yi;
        for (size_t j = i; j < i+N; j++) {
            #pragma HLS PIPELINE off
            xc  = x.buf[i] + c;
            c = xc < c;
            yi = y.buf[i];
            xc += yi;
            c += xc < yi;
            z.buf[j] = xc;
        }

	}
}

//左ビットシフト
void shlT(ap_uint<256> z[N], const ap_uint<256> x[N], size_t bit)
{
    #pragma HLS pipeline off
    const size_t UnitBitSize=256;
    size_t bitRev = UnitBitSize - bit;
    ap_uint<256> prev = x[N - 1];
    ap_uint<256> keep = prev;
    ap_uint<256> t;
	for (size_t i = N - 1; i > 0; i--) {
		t = x[i - 1];
		z[i] = (prev << bit) | (t >> bitRev);
		prev = t;
	}
	z[0] = prev << bit;
	//return keep >> bitRev;
}

void shrT(ap_uint<256> z[N], const ap_uint<256> x[N], size_t bit)
{
    #pragma HLS pipeline off
    const size_t UnitBitSize = 256;
	size_t bitRev = UnitBitSize - bit;
    ap_uint<256> t;
	ap_uint<256> prev = x[0];
	for (size_t i = 1; i < N; i++) {
		t = x[i];
		z[i - 1] = (prev >> bit) | (t << bitRev);
		prev = t;
	}
	z[N - 1] = prev >> bit;
}

bool cmpGeT(const ap_uint<256> px[N], const ap_uint<256> py[N])
{
	for (size_t i = 0; i < N; i++) {
        #pragma HLS pipeline off
		const ap_uint<256> x = px[N - 1 - i];
		const ap_uint<256> y = py[N - 1 - i];
		if (x > y) return true;
		if (x < y) return false;
	}
	return true;
}

void copyT(uint2048_t z, const uint2048_t x)
{
	for(int i=0;i<N;i++){
		z.buf[i]=x.buf[i];
	}
}
