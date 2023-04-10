#include "fp.h"
#include "ap_int.h"

// z[N] = x[N] + y[N]
uint64_t addT(uint64_t* z, const uint64_t* x, const uint64_t* y)
{
	uint64_t c = 0;
	for (size_t i = 0; i < N; ++i) {
		uint64_t xc = x[i] + c;
		c = xc < c;
		uint64_t yi = y[i];
		xc += yi;
		c += xc < yi;
		z[i] = xc;
	}
	return c;
}

// z[N] = x[N] - y[N]
uint64_t subT(uint64_t* z, const uint64_t* x, const uint64_t* y)
{
	uint64_t c = 0;
	for (size_t i = 0; i < N; ++i) {
		uint64_t yi = y[i];
		yi += c;
		c = yi < c;
		uint64_t xi = x[i];
		c += xi < yi;
		z[i] = xi - yi;
	}
	return c;
}

uint64_t mulUnit1(uint64_t* pH, uint64_t x, uint64_t y)
{
	ap_uint<128> t;
	t = x * y;
	*pH = uint64_t(t >> 64);
	return uint64_t(t);
}

uint64_t mulUnitT(uint64_t* z, const uint64_t* x, const uint64_t y[])
{
	uint64_t H = 0;
	for (size_t i = 0; i < N; i++) {
		uint64_t t = H;
		uint64_t L = mulUnit1(&H, x[i], y[0]);
		z[i] = t + L;
		if (z[i] < t) {
			H++;
		}
	}
	return H; // z[n]
}

uint64_t mulUnitAddT(uint64_t* z, const uint64_t* x, const uint64_t y[])
{
	uint64_t xy[N], ret;
	ret = mulUnitT(xy, x, y);
	ret += addT(z, z, xy);
	return ret;
}

void mulT(uint64_t pz[N+1], const uint64_t px[], const uint64_t py[])
{
	pz[N] = mulUnitT(pz, px, py);
	for (size_t i = 1; i < N; i++) {
		pz[N + i] = mulUnitAddT(&pz[i], px, &py[i]);
	}
}

// py[2N] = px[N]^2
void sqrT(uint64_t* py, const uint64_t* px)
{
	mulT(py, px, px);
}
