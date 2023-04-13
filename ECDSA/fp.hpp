struct mon {
	const ap_uint<256> mod;
	const size_t nbit;
	const ap_uint<256> R;
	const ap_uint<256> R2;
	const ap_uint<256> nr;
	const ap_uint<256> R2mon;
	const ap_uint<256> inv4;
};

extern mon para;

void addMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y);
void subMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y);
void mulMont(ap_uint<256>& z, const ap_uint<512> x);
void mulMod(ap_uint<256>& z, const ap_uint<256> x, const ap_uint<256> y);
void sqrMod(ap_uint<256>& z, const ap_uint<256> x);
