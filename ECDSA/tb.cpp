#include "bint.hpp"
#include "fp.hpp"

int main(void)
{
	ap_uint<256> a,b,c;
	ap_uint<512> x;

	a="56444717392532950066703248216298613406963050146664185407156138575012476696839";
	b="20812168509434597367146703229805575690060615791308155437936410982393987532344";

	subMod(c,a,b);
	std::cout << c << std::endl;

	return 0;
}
