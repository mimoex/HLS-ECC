#include "fp.h"


Point ec_add(Point& p, Point& q, const long long int& a, const long long int& mod)
{
	if (p.inf) { return q; cout << "p is inf" << endl; }
	if (q.inf) { return p; cout << "q is inf" << endl; }

	long long int lambda_temp, y_1, lambda;
	long long int lh, rh;
	Point result;


	//cout << "Px,Qx:" << p.x << "," << q.x << endl;
	if (p.x == q.x) {
		//P + (-P) = 0
		//cout << "Py,-Py:" << p.y << "," << -q.y << endl;
		if (p.y == -q.y) {
			p.inf = true;
			return p;
		}
		//lambda=(3*x1*x1+a)/(2*y1)
		mul_fp(p.x, p.x, mod, &lambda_temp);
		mul_fp(3, lambda_temp, mod, &lambda_temp);
		add_fp(lambda_temp, a, mod, &lambda_temp);

		add_fp(p.y, p.y, mod, &y_1);

		div_fp(lambda_temp, y_1, mod, &lambda);
	}
	else {
		//x1!=x2‚Ì‚Æ‚«C
		// cout << "Add" << endl;
		//lambda=(y2-y1)/(x2-x1)
		sub_fp(p.y, q.y, mod, &lh);
		sub_fp(p.x, q.x, mod, &rh);
		div_fp(lh, rh, mod, &lambda);
	}

	//P+Q‚ÌxÀ•W
	long long int lambda2, x_temp;
	mul_fp(lambda, lambda, mod, &lambda2);
	add_fp(p.x, q.x, mod, &x_temp);
	sub_fp(lambda2, x_temp, mod, &result.x);

	//P+Q‚ÌyÀ•W
	sub_fp(p.x, result.x, mod, &x_temp);

	mul_fp(lambda, x_temp, mod, &lambda2);
	sub_fp(lambda2, p.y, mod, &result.y);

	return result;
}

Point copy_Point(Point& p) {
	Point result;
	result.x = p.x;
	result.y = p.y;
	result.inf = p.inf;
	return p;
}
