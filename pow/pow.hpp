#include <iostream>
#include <ap_int.h>

//typedef ap_uint<64> uint64;
//typedef ap_uint<128> uint128;
//typedef ap_uint<256> uint256;
//typedef ap_uint<512> uint512;

struct mon {
	size_t nbit;
	ap_uint<256> R, R2, nr, modp;
};

int get_msb(ap_uint<256>  n);
ap_uint<256>  left2right_binary(ap_uint<256>  a, ap_uint<256>  n, mon para);

ap_uint<256> pow(const ap_uint<256> x, const ap_uint<256> n, const mon para);


ap_uint<256> MR(const ap_uint<256> a, const ap_uint<256> b, const mon& para);
