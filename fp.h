#include <iostream>

using namespace std;


struct Point {
	long long int x, y;
	bool inf = false;
};


//�L���̂̉��Z	c=a+b%p
void add_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//�L���̂̌��Z	c=a-b%p
void sub_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//�L���̂̏�Z	c=a*b%p
void mul_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//�L���ׂ̂̂���	c=a^b%p
void pow_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//�L���̂̋t��	c=a^-1
void inv_fp(const long long int& a, const long long int& p, long long int** c);
//�L���̂̏��Z	c=a/b%p
void div_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);

Point ec_add(Point& p, Point& q, const long long int& a, const long long int& mod);

Point copy_Point (Point& p);
