#include "pow.hpp"

ap_uint<256> sliding_window(const ap_uint<256> a, const ap_uint<256> n, mon para);

ap_uint<256> amari(ap_uint<256> x, ap_uint<256> y, mon para);

ap_uint<256> addMod(const ap_uint<256> x, const ap_uint<256> y, mon para);
ap_uint<256> addModSlow(const ap_uint<256> x, const ap_uint<256> y, mon para);


int main(void)
{

	ap_uint<256> a="112889434785065900135211481371037383646282385554418514861667765615237067913479";
	//ap_uint<256> n="0b1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110";
	//ap_uint<256> n="0b1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	ap_uint<256>  n="83248674037738389458384410763075677577692607669239377194943530476071658065009";
	ap_uint<256>  ans;

	mon secp256kpara;
	secp256kpara.modp="0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";
	secp256kpara.nbit=256;
	secp256kpara.R="115792089237316195423570985008687907853269984665640564039457584007913129639935"; //256bitの'1'
	secp256kpara.R2="18446752466076602529";
	secp256kpara.nr="91248989341183975618893650062416139444822672217621753343178995607987479196977";

	ans=sliding_window(a,n,secp256kpara);
	//ans=left2right_binary(a,n,secp256kpara);
	//ans=pow(a,n,secp256kpara);
	//ans=amari(a,n,secp256kpara);
	//ans = MR(a,n,secp256kpara);
	//ans = addModSlow(a,n,secp256kpara);
	std::cout<<ans<<std::endl;

	return 0;

}