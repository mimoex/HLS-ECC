#include "Montgomery.hpp"

using namespace std;

void curve25519_binary_check()
{
	mpz_class a = 486662;
	Point p, q, result;
	Point A_point;

	mpz_class showx,showz;

	p.X = 9;
	p.Z = 1;
	//p.Z = "0x20ae19a1b8a086b4e01edd2c7748d14c923d4d7e6d7c61b229e9c5a27eced3d9";

	
	
	A_point.X = a;
	A_point.Z = 1;

	for (int n = 1; n < 11; n++) {

		result = xMUL(p, A_point, n);
		if (result.Z==0) {
			cout << "Inf\n" << endl;
		}
		else {
			div_fp(&showx, result.X, result.Z);
			cout << n << "P=0x" << showx.get_str(16) << endl;
			cout << endl;
		}

	}
}

void calcinv4()
{
	mpz_class res;
	inv_fp(&res, 4);

	cout << res << endl;
}

int main(void)
{
	curve25519_binary_check();
	return 0;
}