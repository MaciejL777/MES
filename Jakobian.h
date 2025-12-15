#pragma once
#include<vector>
#include "ElemUniw.h"
#include <cmath>
class Jakobian {
public:
    double J[4][4];
    double J1[4][4];
    double detJ;
    static ElemUniv *Univ;
    Jakobian(int point, double* x,double *y);
    static void setUniv(ElemUniv* ele) { Univ = ele; }
};