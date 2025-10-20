#pragma once
#include<vector>
#include "GlobalData.h"
#include <cmath>
class Jakobian: public ElemUniv {
public:
    double J[4][4];
    double J1[4][4];
    double detJ;
    Jakobian(int point, double* x,double *y);
};