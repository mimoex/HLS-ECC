#include <iostream>
#include "ap_int.h"

using namespace std;

void mulmod (const ap_uint<256> &a, const ap_uint<256> &b, const ap_uint<256> &p, ap_uint<256> *c);

int main()
{
	ap_uint<256> a, b, p, c;
	p="0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed";
	a="20812168509434597367146703229805575690060615791308155437936410982393987532344";
	b="56444717392532950066703248216298613406963050146664185407156138575012476696839";
	mulmod(a,b,p,&c);

	cout <<c<<endl;
	return 0;
}
