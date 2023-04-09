#include "fp.hpp"

using namespace std;

void curve25519()
{
	ap_uint<256> n, show_x;

	Point result;
	n= ap_uint<256>("0x6a83f2346a72f1ee2c649f1cb84720ebf733304493b606b57b5c341b8de8aa06");
	//n= ap_uint<256>("0x3");

	result=xMUL(n);
	//cout << result.X << ", " << result.Z << endl;


	div_fp(&show_x, result.X, result.Z);
	cout << n << "P=" <<hex<< show_x << endl;
}

void test_fp()
{
	ap_uint<256> x, y, z;
	x = "20812168509434597367146703229805575690060615791308155437936410982393987532344";
	y = "56444717392532950066703248216298613406963050146664185407156138575012476696839";
	div_fp(&z, x, y);
	cout << z << endl;
}


int main()
{
	//test_fp();
	curve25519();
	return 0;
}
