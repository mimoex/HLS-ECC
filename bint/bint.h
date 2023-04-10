#include <iostream>

const size_t N = 4;

struct Fp {
	uint64_t v[N]{};
};
struct FpDbl {
	uint64_t v[N*2]{};
};


uint64_t addT(uint64_t* z, const uint64_t* x, const uint64_t* y);

uint64_t subT(uint64_t* z, const uint64_t* x, const uint64_t* y);

void mulT(uint64_t* pz, const uint64_t* px, const uint64_t* py);

void sqrT(uint64_t* py, const uint64_t* px);
