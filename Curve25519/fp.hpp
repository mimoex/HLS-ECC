#pragma once
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <chrono>
#include <random>

//montgomery剰余乗算
struct mon {
    //montgomery剰余乗算
    const mpz_class mod;
    const mpz_class inv4;
    //const mpz_class sqrt4;    //4*(sqrt(mod))
    const size_t nbit;
    const mpz_class R;
    const mpz_class R2;
    const mpz_class nr;

    const mpz_class mrR2;
};
extern mon para;

struct Point {
    mpz_class X, Z;
};

//有限体の加算	c=a+b %p
void add_fp(mpz_class* c, const mpz_class& a, const mpz_class& b);
//有限体の減算	c=a-b %p
void sub_fp(mpz_class* c, const mpz_class& a, const mpz_class& b);
//有限体の乗算	c=a*b %p
void mul_fp(mpz_class* c, const mpz_class& a, const mpz_class& b);
//有限体のべき乗	c=a^b %p
void pow_fp(mpz_class* c, const mpz_class& a, const mpz_class& b);
//有限体の逆元	c=a^-1
void inv_fp(mpz_class* c, const mpz_class& a);
//有限体の除算	c=a/b %p
void div_fp(mpz_class* c, const mpz_class& a, const mpz_class& b);
//有限体の2乗	c=a^2 %p
void sqr_fp(mpz_class* c, const mpz_class& a);
