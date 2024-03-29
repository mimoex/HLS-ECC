#include <iostream>

using namespace std;


struct Point {
	long long int x, y;
	bool inf = false;
};


//有限体の加算	c=a+b%p
void add_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//有限体の減算	c=a-b%p
void sub_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//有限体の乗算	c=a*b%p
void mul_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//有限体のべき乗	c=a^b%p
void pow_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//有限体の逆元	c=a^-1
void inv_fp(const long long int& a, const long long int& p, long long int** c);
//有限体の除算	c=a/b%p
void div_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);

Point ec_add(Point& p, Point& q, const long long int& a, const long long int& mod);

Point copy_Point (Point& p);
