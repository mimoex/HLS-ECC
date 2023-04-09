#pragma once
#include "fp.hpp"

Point xMUL(const Point& P, const Point& A_1, const mpz_class& n);

void xDBLADDmon(const Point& Pm, const Point& Qm, const Point& Rm, const Point& Ap24m, Point& DBLout, Point& ADDout);