#include "fp.hpp"

// https://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#doubling-dbl-1987-m-2
Point xDBLmon(const Point& Pm, const Point& Ap24m)
{
	ap_uint<256> t0, t1, t2, t3;
	Point resultm;

	sub_fp(&t0, Pm.X, Pm.Z);
	add_fp(&t1, Pm.X, Pm.Z);
	mul_mon(&t0, t0, t0);

	mul_mon(&t1, t1, t1);

	mul_mon(&resultm.Z, Ap24m.Z, t0);
	mul_mon(&resultm.X, resultm.Z, t1);

	sub_fp(&t2, t1, t0);
	mul_mon(&t3, Ap24m.X, t2);

	add_fp(&resultm.Z, resultm.Z, t3);

	mul_mon(&resultm.Z, resultm.Z, t2);
	return resultm;
}

void xDBLADDmon(const Point& Pm, const Point& Qm, const Point& Rm, const Point& Ap24m,
	Point& DBLout, Point& ADDout)
{
#pragma HLS inline off
	ap_uint<256> t0, t1, t2;

	add_fp(&t0, Pm.X, Pm.Z);	//A = X2+Z2
	sub_fp(&t1, Pm.X, Pm.Z);	//B = X2-Z2
	mul_mon(&DBLout.X, t0, t0);		//AA = A2
	sub_fp(&t2, Qm.X, Qm.Z);	//D = X3-Z3

	add_fp(&ADDout.X, Qm.X, Qm.Z);	//C = X3+Z3
	mul_mon(&t0, t0, t2);			//DA = D*A
	mul_mon(&DBLout.Z, t1, t1);			//BB = B2

	mul_mon(&t1, t1, ADDout.X);		//CB = C*B
	sub_fp(&t2, DBLout.X, DBLout.Z);	//E = AA-BB
	mul_mon(&DBLout.X, DBLout.X, DBLout.Z);	//X4 = AA*BB

	mul_mon(&ADDout.X, Ap24m.X, t2);		//a24*E
	sub_fp(&ADDout.Z, t0, t1);	//DA-CB
	add_fp(&DBLout.Z, DBLout.Z, ADDout.X);	//(BB+a24*E)
	add_fp(&ADDout.X, t0, t1);	//DA+CB

	mul_mon(&DBLout.Z, DBLout.Z, t2);	//Z4 = E*(BB+a24*E)
	mul_mon(&ADDout.Z, ADDout.Z, ADDout.Z);		//(DA-CB)2
	mul_mon(&ADDout.X, ADDout.X, ADDout.X);		//X5 = (DA+CB)2
	mul_mon(&ADDout.Z, ADDout.Z, Rm.X);	//Z5 = X1*(DA-CB)2
	mul_mon(&ADDout.X, ADDout.X, Rm.Z);
}


//ÉÇÉìÉSÉÅÉäã»ê¸ÇÃÉXÉJÉâÅ[î{
Point xMUL(const ap_uint<256>& n) {
#pragma HLS allocation function instances=MR limit=1
	Point A_1, P;
	A_1.X=486662;
	A_1.Z=1;

		P.X=9;
		P.Z=1;
	Point x0, Ap24_1,Ap24_0;
	Point x0m, x1m, Pm, Ap24_1m;
	int i;

	//MontgomeryÇÃê¢äEÇ÷
	mul_mon(&Pm.X, P.X, para.R2);
	mul_mon(&Pm.Z, P.Z, para.R2);

	//x0 = P;
	x0m=Pm;

	//a24ÇÃåvéZ
	Ap24_1.Z = 1;
	add_fp(&Ap24_0.X, A_1.X, 2);

	mul_fp(&Ap24_1.X, Ap24_0.X, para.inv4);

	//MontgomeryÇÃê¢äEÇ÷
	mul_mon(&Ap24_1m.X, Ap24_1.X, para.R2);
	mul_mon(&Ap24_1m.Z, Ap24_1.Z, para.R2);

	ec_double : x1m = xDBLmon(Pm, Ap24_1m);

	size_t bit_size=256;
	get_bits : for (i = 255; i > 0; i--) {
	#pragma HLS PIPELINE off
			if (n[i] == 1){
				break;
			}
			bit_size-=1;
		}

	ec_binary : for (i = bit_size - 2; i >= 0; --i) {
#pragma HLS PIPELINE off
		if (n[i] == 0) ec_dbladd_1 : xDBLADDmon(x0m, x1m, Pm, Ap24_1m, x0m, x1m);
		else ec_dbladd_2 : xDBLADDmon(x1m, x0m, Pm, Ap24_1m, x1m, x0m);
	}
	MR(x0m.X,&x0.X);
	MR(x0m.Z,&x0.Z);
	return x0;
}
