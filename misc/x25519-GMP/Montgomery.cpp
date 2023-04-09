#include "fp.hpp"

using namespace std;

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#doubling-dbl-1987-m-2
Point xDBLmon(const Point& Pm, const Point& Ap24m)
{
	mpz_class t0, t1, t2, t3;
	mpz_class temp1, temp2, temp3, temp4, temp5, temp6;
	Point resultm;

	sub_fp(&t0, Pm.X, Pm.Z);
	add_fp(&t1, Pm.X, Pm.Z);
	sqr_mon(&t0, t0);

	sqr_mon(&t1, t1);

	mul_mon(&resultm.Z, Ap24m.Z, t0);
	mul_mon(&resultm.X, resultm.Z, t1);

	sub_fp(&t2, t1, t0);
	mul_mon(&t3, Ap24m.X, t2);

	add_fp(&resultm.Z, resultm.Z, t3);

	mul_mon(&resultm.Z, resultm.Z, t2);
	return resultm;
}

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#ladder-ladd-1987-m-3
void xDBLADDmon(const Point& Pm, const Point& Qm, const Point& Rm, const Point& Ap24m,
	Point& DBLout, Point& ADDout) {
	mpz_class t0, t1, t2;

	add_fp(&t0, Pm.X, Pm.Z);	//A = X2+Z2
	sub_fp(&t1, Pm.X, Pm.Z);	//B = X2-Z2
	sqr_mon(&DBLout.X, t0);		//AA = A2
	sub_fp(&t2, Qm.X, Qm.Z);	//D = X3-Z3

	add_fp(&ADDout.X, Qm.X, Qm.Z);	//C = X3+Z3
	mul_mon(&t0, t0, t2);			//DA = D*A
	sqr_mon(&DBLout.Z, t1);			//BB = B2

	mul_mon(&t1, t1, ADDout.X);		//CB = C*B
	sub_fp(&t2, DBLout.X, DBLout.Z);	//E = AA-BB
	mul_mon(&DBLout.X, DBLout.X, DBLout.Z);	//X4 = AA*BB

	mul_mon(&ADDout.X, Ap24m.X, t2);		//a24*E
	sub_fp(&ADDout.Z, t0, t1);	//DA-CB
	add_fp(&DBLout.Z, DBLout.Z, ADDout.X);	//(BB+a24*E)
	add_fp(&ADDout.X, t0, t1);	//DA+CB

	mul_mon(&DBLout.Z, DBLout.Z, t2);	//Z4 = E*(BB+a24*E)
	sqr_mon(&ADDout.Z, ADDout.Z);		//(DA-CB)2
	sqr_mon(&ADDout.X, ADDout.X);		//X5 = (DA+CB)2
	mul_mon(&ADDout.Z, ADDout.Z, Rm.X);	//Z5 = X1*(DA-CB)2
	mul_mon(&ADDout.X, ADDout.X, Rm.Z);
}

//モンゴメリ曲線のスカラー倍
Point xMUL(const Point& P, const Point& A_1, const mpz_class& n) {
	Point Ap24_1, Ap24_0;
	Point x0m, x1m, Ap24_1m, x0;
	Point Pm;

	Pm = normal2mon(P);

	x0m = Pm;

	//a24の計算
	Ap24_1.Z = 1;
	add_fp(&Ap24_0.X, A_1.X, 2);

	mul_fp(&Ap24_1.X, Ap24_0.X, para.inv4);
	Ap24_1m = normal2mon(Ap24_1);

	x1m = xDBLmon(Pm, Ap24_1m);

	size_t bit_size;
	bit_size = mpz_sizeinbase(n.get_mpz_t(), 2);

	//cout << "n=" << n << " = 0b" << n.get_str(2) << endl;

	for (int i = bit_size - 2; i >= 0; i--) {
		if (mpz_tstbit(n.get_mpz_t(), i) == 0) xDBLADDmon(x0m, x1m, Pm, Ap24_1m, x0m, x1m);
		else xDBLADDmon(x1m, x0m, Pm, Ap24_1m, x1m, x0m);
	}
	x0.X = MR(x0m.X);
	x0.Z = MR(x0m.Z);
	return x0;
}