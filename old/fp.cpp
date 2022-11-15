#include "fp.h"

void add_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c)
{
	*c = a + b;
	if (*c >= p) *c -= p;
	*c = *c % p;
}

void sub_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c)
{
	*c = (a - b);
	*c = (*c % p + p) % p;
}


void mul_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c)
{
	*c = a * b;
	*c = *c % p;
}


void pow_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c)
{
	*c = a;
	for (int i = 1; i < b; i++) {
		*c *= a;
		*c = *c % p;
	}
	
	
}

//‹tŒ³
void inv_fp(const long long int& a, const long long int& p, long long int** c)
{
	if (a == 0) {
		cout << "zero inv" << endl;

	}
	else {
		pow_fp(a, p - 2, p, *c);
	}

}

void div_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c)
{
	inv_fp(b, p, &c);
	mul_fp(a, *c, p, c);

}