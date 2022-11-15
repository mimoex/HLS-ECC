#include "fp.hpp"

using namespace std;

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#diffadd-dadd-1987-m-3
Point Montgomery_ADDmon(const Point& Pm, const Point& Qm, const Point& Rm) {
	mpz_class A, B, C, D, DA, CB, temp1, temp2, temp3, temp4;
	Point resultm;

	add_fp(&A, Qm.X, Qm.Z);
	sub_fp(&B, Qm.X, Qm.Z);
	add_fp(&C, Pm.X, Pm.Z);
	sub_fp(&D, Pm.X, Pm.Z);
	mul_fp(&DA, D, A);
	mul_fp(&CB, B, C);
	add_fp(&temp1, DA, CB);
	sqr_fp(&temp2, temp1);
	mul_fp(&resultm.X, Rm.Z, temp2);
	sub_fp(&temp3, DA, CB);
	sqr_fp(&temp4, temp3);
	mul_fp(&resultm.Z, Rm.X, temp4);
	return resultm;
}

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#doubling-dbl-1987-m-2
Point xDBLmon(const Point& Pm, const Point& Ap24m)
{
	mpz_class t0, t1, t2, t3;
	mpz_class temp1, temp2, temp3, temp4, temp5, temp6;
	Point resultm;

	sub_fp(&t0, Pm.X, Pm.Z);
	add_fp(&t1, Pm.X, Pm.Z);
	sqr_fp(&t0, t0);

	sqr_fp(&t1, t1);

	mul_fp(&resultm.Z, Ap24m.Z, t0);
	mul_fp(&resultm.X, resultm.Z, t1);

	sub_fp(&t2, t1, t0);
	mul_fp(&t3, Ap24m.X, t2);

	add_fp(&resultm.Z, resultm.Z, t3);

	mul_fp(&resultm.Z, resultm.Z, t2);
	return resultm;
}

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#ladder-ladd-1987-m-3
void xDBLADDmon(const Point& Pm, const Point& Qm, const Point& Rm, const Point& Ap24m,
	Point& DBLout, Point& ADDout) {
	mpz_class t0, t1, t2;

	add_fp(&t0, Pm.X, Pm.Z);	//A = X2+Z2
	sub_fp(&t1, Pm.X, Pm.Z);	//B = X2-Z2
	sqr_fp(&DBLout.X, t0);		//AA = A2
	sub_fp(&t2, Qm.X, Qm.Z);	//D = X3-Z3

	add_fp(&ADDout.X, Qm.X, Qm.Z);	//C = X3+Z3
	mul_fp(&t0, t0, t2);			//DA = D*A
	sqr_fp(&DBLout.Z, t1);			//BB = B2

	mul_fp(&t1, t1, ADDout.X);		//CB = C*B
	sub_fp(&t2, DBLout.X, DBLout.Z);	//E = AA-BB
	mul_fp(&DBLout.X, DBLout.X, DBLout.Z);	//X4 = AA*BB

	mul_fp(&ADDout.X, Ap24m.X, t2);		//a24*E
	sub_fp(&ADDout.Z, t0, t1);	//DA-CB
	add_fp(&DBLout.Z, DBLout.Z, ADDout.X);	//(BB+a24*E)
	add_fp(&ADDout.X, t0, t1);	//DA+CB

	mul_fp(&DBLout.Z, DBLout.Z, t2);	//Z4 = E*(BB+a24*E)
	sqr_fp(&ADDout.Z, ADDout.Z);		//(DA-CB)2
	sqr_fp(&ADDout.X, ADDout.X);		//X5 = (DA+CB)2
	mul_fp(&ADDout.Z, ADDout.Z, Rm.X);	//Z5 = X1*(DA-CB)2
	mul_fp(&ADDout.X, ADDout.X, Rm.Z);
}

//モンゴメリ曲線のスカラー倍
Point xMUL(const Point& P, const Point& A_1, const mpz_class& n) {
	Point Ap24_1, Ap24_0;
	Point x0, x1, Ap24_1m;

	x0 = P;
	//x0m.X = P.X;
	//x0m.Z = P.Z;
	//x0.X = 0;
	//x0.Z = 0;

	//a24の計算
	Ap24_0.Z = 1;
	add_fp(&Ap24_0.X, A_1.X, 2);

	mul_fp(&Ap24_1.X, Ap24_0.X, para.inv4);
	Ap24_1.Z = 1;

	x1 = xDBLmon(P, Ap24_1);

	size_t bit_size;
	bit_size = mpz_sizeinbase(n.get_mpz_t(), 2);

	//cout << "n=" << n << " = 0b" << n.get_str(2) << endl;

	for (int i = bit_size - 2; i >= 0; i--) {
		if (mpz_tstbit(n.get_mpz_t(), i) == 0) xDBLADDmon(x0, x1, P, Ap24_1, x0, x1);
		else xDBLADDmon(x1, x0, P, Ap24_1, x1, x0);
	}
	return x0;
}