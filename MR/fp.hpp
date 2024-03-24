#include <iostream>
#include "ap_int.h"

const size_t N = 4;

struct Fp {
	uint64_t v[N]{};
};

struct FpDbl {
	uint64_t v[N * 2]{};
};

static Fp modp;
//static uint64_t nbit;
static Fp R;
static Fp R2;
static Fp nr;

struct Point {
	Fp X,Z;
};

//bint
//add
uint64_t addT(uint64_t* z, const uint64_t* x, const uint64_t* y);

//sub
uint64_t subT(uint64_t* z, const uint64_t* x, const uint64_t* y);

//mul
void mulT(uint64_t pz[N+1], const uint64_t px[], const uint64_t py[]);

//sqr
void sqrT(uint64_t* py, const uint64_t* px);

