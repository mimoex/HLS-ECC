#include "fp.h"

int main(void)
{
	Fp a, b, c;
	FpDbl x;
	a.v[0] = 8;
	b.v[0] = 5;



	mulT(x.v, a.v, b.v);
	for (size_t i = 0; i < N; i++) {
		std::cout << x.v[i] << std::endl;
	}
	return 0;
}
