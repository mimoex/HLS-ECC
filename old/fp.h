#include <iostream>

using namespace std;


struct Point {
	long long int x, y;
	bool inf = false;
};


//—LŒÀ‘Ì‚Ì‰ÁZ	c=a+b%p
void add_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//—LŒÀ‘Ì‚ÌŒ¸Z	c=a-b%p
void sub_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//—LŒÀ‘Ì‚ÌæZ	c=a*b%p
void mul_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//—LŒÀ‘Ì‚Ì‚×‚«æ	c=a^b%p
void pow_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);
//—LŒÀ‘Ì‚Ì‹tŒ³	c=a^-1
void inv_fp(const long long int& a, const long long int& p, long long int** c);
//—LŒÀ‘Ì‚ÌœZ	c=a/b%p
void div_fp(const long long int& a, const long long int& b, const long long int& p, long long int* c);

Point ec_add(Point& p, Point& q, const long long int& a, const long long int& mod);

Point copy_Point (Point& p);
