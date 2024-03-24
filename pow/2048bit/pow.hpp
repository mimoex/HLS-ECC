#include <iostream>
#include <ap_int.h>

const size_t N=8;

// 2048bitの整数を表現する
struct uint2048_t {
  ap_uint<256> buf[N] {};
};
struct uint4096_t {
	ap_uint<256> buf[N*2] {};
};

struct mon {
	size_t nbit;
	uint2048_t R, R2, nr, modp;
};

ap_uint<256> addT(ap_uint<256> z[N], const ap_uint<256> x[N], const ap_uint<256> y[N]);
ap_uint<256> subT(ap_uint<256> z[N], const ap_uint<256> x[N], const ap_uint<256> y[N]);
void mul(uint4096_t& z, const uint2048_t& x, const uint2048_t& y);

void shrT(ap_uint<256> z[N], const ap_uint<256> x[N], size_t bit);
void shlT(ap_uint<256> z[N], const ap_uint<256> x[N], size_t bit);

bool cmpGeT(const ap_uint<256> px[N], const ap_uint<256> py[N]);

void copyT(uint2048_t z, const uint2048_t x);


uint2048_t mul_fp(const uint2048_t a, const uint2048_t b, const mon& para);

void binary(uint2048_t z, const uint2048_t x, const uint2048_t y, mon para);
uint2048_t sliding_window(const uint2048_t x, const uint2048_t y, mon para);
