#pragma once
#include "ElemUniw.h"
#include <cmath>

class Gauss {
    double (*ff1d)(double) = nullptr;
    double (*ff2d)(double, double) = nullptr;
public:
   
    Gauss(){}
    Gauss(double (*ff1)(double));
    Gauss(double (*ff2)(double, double));
    double Integrate1d(int num_points);
    double Integrate2d(int num_points);
    void SetFunction1d(double (*ff1)(double));
    void SetFunction2d(double (*ff2)(double, double));
};
double fx(double x);
double fxy(double x, double y);

