#include "fp.hpp"

Point PointDbl(const Point& p, const ap_uint<256>& a)
{
#pragma HLS INLINE OFF
#pragma HLS PIPELINE off
	ap_uint<256> XX, ZZ, w_temp1, w_temp2, w, s_temp, s, ss, R, RR, XaddR, B_temp1, XXaddRR, B, ww, B2, h, Ylh, Y_temp1, Yrh;
	Point result;
	mul_fp(XX, p.X, p.X);
	mul_fp(ZZ, p.Z, p.Z);

	mul_fp(w_temp1, a, ZZ);
	mul_fp(w_temp2, 3, XX);
	add_fp(w, w_temp1, w_temp2);

	mul_fp(s_temp, 2, p.Y);
	mul_fp(s, s_temp, p.Z);

	mul_fp(ss, s, s);

	mul_fp(result.Z, s, ss);

	mul_fp(R, p.Y, s);

	mul_fp(RR, R, R );

	add_fp(XaddR, p.X, R);
	mul_fp(B_temp1, XaddR, XaddR);
	add_fp(XXaddRR, XX, RR);
	sub_fp(B, B_temp1, XXaddRR);

	mul_fp(ww, w, w);
	mul_fp(B2, 2, B);
	sub_fp(h, ww, B2);

	mul_fp(result.X, h, s);

	sub_fp(Y_temp1, B, h);
	mul_fp(Ylh, w, Y_temp1);
	mul_fp(Yrh, 2, RR);
	sub_fp(result.Y, Ylh, Yrh);
	return result;
}

Point PointAdd(const Point& p, const Point& q)
{
#pragma HLS INLINE OFF
#pragma HLS PIPELINE off

	if (p.Z == 0) return q;
	if (q.Z == 0) return p;


	ap_uint<256> t0, t1, u0, u1, t, tt, u, u2, v, w, u3, X3, Y3, Z3, w_temp1, w_temp2, addu;
	ap_uint<256> Ytemp1, Ytemp2, Ytemp3, Ytemp4;
	Point result;
	mul_fp(t0, p.Y, q.Z);
	mul_fp(t1, q.Y, p.Z);

	mul_fp(u0, p.X, q.Z);
	mul_fp(u1, q.X, p.Z);

	sub_fp(t, t0, t1);
	sub_fp(u, u0, u1);

	mul_fp(u2, u, u);
	mul_fp(v, p.Z, q.Z);

	mul_fp(tt, t, t);
	mul_fp(w_temp1, tt, v);
	add_fp(addu, u0, u1);
	mul_fp(w_temp2, u2, addu);
	sub_fp(w, w_temp1, w_temp2);
	mul_fp(u3, u, u2);

	mul_fp(result.X, u, w);

	mul_fp(Ytemp1, u0, u2);
	sub_fp(Ytemp2, Ytemp1, w);
	mul_fp(Ytemp3,Ytemp2, t);
	mul_fp(Ytemp4, t0, u3);
	sub_fp(result.Y, Ytemp3, Ytemp4);

	mul_fp(result.Z, u3, v);
	return result;
}


Point add_affine(const Point& P, const Point& Q, const ap_uint<256>& a)
{
#pragma HLS INLINE OFF
//#pragma HLS ALLOCATION function instances=mul_fp limit=1
//#pragma HLS ALLOCATION function instances=div_fp limit=1
#pragma HLS PIPELINE off
	if(P.isZero)
		return Q;
	if(Q.isZero)
		return P;
	Point res;
	ap_uint<256> lambda_temp, y_1, lambda, lh, rh;;
	if(P.X==Q.X){
		if(P.Y==-Q.Y){
			res.isZero=true;
			return res;
		}
		mul_fp(lambda_temp,P.X,P.X);
		mul_fp(lambda_temp,3,lambda_temp);
		add_fp(lambda_temp,lambda_temp,a);
		add_fp(y_1,P.Y,P.Y);
		div_fp(lambda, lambda_temp, y_1);
	} else {
		sub_fp(lh,P.Y,Q.Y);
		sub_fp(rh,P.X,Q.X);
		div_fp(lambda, lh, rh);
	}

	ap_uint<256> lambda2, x_temp;

	mul_fp(lambda2,lambda,lambda);
	add_fp(x_temp,P.X,Q.X);
	sub_fp(res.X, lambda2, x_temp);

	sub_fp(x_temp, P.X, res.X);
	mul_fp(lambda2, lambda,x_temp);
	sub_fp(res.Y, lambda2,P.Y);

	return res;

}

int max(const int a, const int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

#define D 30

Point xMUL() {
#pragma HLS PIPELINE OFF
	Point A_1, P, RES, tempPoint;


	A_1.X=1; //a=1;
	A_1.Z=7; //b=7;

	P.X="0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
	P.Y="0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";
	P.Z=1;
	int i;

	ap_uint<256> nn= ap_uint<256>("0xF99527E2862042DBB66313F44C4C47B6C0259E16F63F000194C4D5BBE3BB3907");


	size_t bit_size=256;

	/*
	ec_binary : for (i = bit_size - 2; i >= 0; i--) {
//#pragma HLS PIPELINE off
		if (nn[i] == 1) ec_dbladd_1 : RES = PointAdd(RES,tempPoint);
		tempPoint=PointDbl(tempPoint, A_1.X);
	}
	return RES;
	*/

	// sliding window method
/*
	Point table[1<<D];
	Point pp;
	table[1] = P;
	pp=PointDbl(P, A_1.X);
	for (i = 1; i < (1 << (D - 1)); i++) {
		table[2*i+1] = PointAdd(table[2*i-1],pp);
	}

	i = bit_size - 1;
	while(i >= 0) {
		if(nn[i]==0){
			RES=PointDbl(RES, A_1.X);
			i--;
		} else {
			int s = max(0, i - D + 1);
			while(nn[s]==0){
				s++;
			}
			for(int j=0; j<i-s+1; ++j){
				RES=PointDbl(RES, A_1.X);
			}

			ap_uint<D> window_bits = nn(s,i);
			RES=PointAdd(RES,table[window_bits]);
			i = s - 1;
		}
	}
	return RES;
*/

	// window method

	Point table[1<<D];
	table[1] = P;
	for (i = 1; i < (1 << D) - 1; i++) {
		table[i+1] = PointAdd(table[i],P);
	}

	i = bit_size - 1;
	while(i >= 0) {
		int s = i-D+1;
		for(int j=0;j<D;j++){
			RES=PointDbl(RES, A_1.X);
		}
			ap_uint<D> window_bits = nn(s,i);
			RES=PointAdd(RES,table[window_bits]);
			i = s - 1;
	}
	return RES;


	// affine
	/*
	ec_binary : for (i = bit_size - 2; i >= 0; --i) {
#pragma HLS PIPELINE off
		if (n[i] == 1) ec_dbladd_1 : RES = add_affine(RES,tempPoint,A_1.X);
		tempPoint=add_affine(tempPoint,tempPoint, A_1.X);
	}
	return RES;
	*/
}

