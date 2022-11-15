#include "fp.hpp"

//Montgomery multiplicatuon
mon para = {
	mpz_class("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed"),
	mpz_class("43422033463993573283839119378257965444976244249615211514796594002967423614962"),
	255,
	mpz_class("57896044618658097711785492504343953926634992332820282019728792003956564819967"),
	mpz_class("361"),
	mpz_class("21330121701610878104342023554231983025602365596302209165163239159352418617883"),
	mpz_class("19")
};


void add_fp(mpz_class* c, const mpz_class& a, const mpz_class& b)
{
	*c = a + b;
	if (*c >= para.mod) *c -= para.mod;
}

void sub_fp(mpz_class* c, const mpz_class& a, const mpz_class& b)
{
	if (a >= b) *c = a - b;
	else *c = a + para.mod - b;
}

void mul_fp(mpz_class* c, const mpz_class& a, const mpz_class& b)
{
	*c = a * b;
	*c %= para.mod;
}


void sqr_fp(mpz_class* c, const mpz_class& a)
{
	*c = a * a;
	*c %= para.mod;
}


void pow_fp(mpz_class* c, const mpz_class& a, const mpz_class& b)
{
	mpz_class result = 1;

	for (int i = para.nbit - 1; i >= 0; i--) {
		mul_fp(&result, result, result);
		if (mpz_tstbit(b.get_mpz_t(), i) == 1) mul_fp(&result, result, a);
	}
	*c = result;
}

//void mul_mon(mpz_class* c, const mpz_class& a, const mpz_class& b)
//{
//	*c = MR(a * b);
//}

//void pow_mon(mpz_class* c, const mpz_class& a, const mpz_class& b)
//{
//	mpz_class result = para.mrR2;
//
//	for (int i = para.nbit - 1; i >= 0; i--) {
//		result = MR(result * result);
//		if (mpz_tstbit(b.get_mpz_t(), i) == 1) result = MR(result * a);
//	}
//	*c = result;
//}

//逆元
void inv_fp(mpz_class* c, const mpz_class& a)
{
	if (a == 0) {
		throw std::range_error("Divided by zero.");

	}
	else {
		pow_fp(c, a, para.mod - 2);
	}

}


void div_fp(mpz_class* c, const mpz_class& a, const mpz_class& b)
{
	inv_fp(c, b);
	mul_fp(c, a, *c);
}
