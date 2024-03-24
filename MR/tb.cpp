#include "fp.hpp"

using namespace std;

int main()
{
	//ap_uint<256> a, b, c;
	Fp a,b,c;
	FpDbl ans;
	//para.mod="0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed";
	modp.v[0]=0xffffffffffffffed;
	modp.v[1]=0xffffffffffffffff;
	modp.v[2]=0xffffffffffffffff;
	modp.v[3]=0x7fffffffffffffff;
	//Fp::nbit=255;
	//para.nr="21330121701610878104342023554231983025602365596302209165163239159352418617883";
	//para.R="57896044618658097711785492504343953926634992332820282019728792003956564819967";
	//para.R2="361";
	//a="20812168509434597367146703229805575690060615791308155437936410982393987532344";
	a.v[0]=0xb85497a9ba510638;
	a.v[1]=0x68e100a50b479104;
	a.v[2]=0xd00b063876877e9d;
	a.v[3]=0x2e03451a7181446f;
	//b="56444717392532950066703248216298613406963050146664185407156138575012476696839";
	b.v[0]=0x94c4d5bbe3bb3907;
	b.v[1]=0xc0259e16f63f0001;
	b.v[2]=0xb66313f44c4c47b6;
	b.v[3]=0x7cca93f14310216d;

	//addT(c.v,a.v,b.v);
	//subT(c.v,b.v,a.v);
	mulT(ans.v,a.v,b.v);

	for(int i=0;i<8;i++){
		cout <<c.v[i]<<","<<endl;
	}

	return 0;
}
