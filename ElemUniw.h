#pragma once
#include<vector>
#include<cmath>
#include"GlobalData.h"
class Surface {
public:
    std::vector<std::vector<double>> N;
    void Next(double ksi, double eta);
};
class ElemUniv  {
public:
    const double points[10] = {
       0,
       sqrt(1.0 / 3.0), -sqrt(1.0 / 3.0),
       0,
       sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0),
       sqrt(3.0 / 7.0 - 2.0 / 7.0 * sqrt(6.0 / 5.0)),
       -sqrt(3.0 / 7.0 - 2.0 / 7.0 * sqrt(6.0 / 5.0)),
       sqrt(3.0 / 7.0 + 2.0 / 7.0 * sqrt(6.0 / 5.0)),
       -sqrt(3.0 / 7.0 + 2.0 / 7.0 * sqrt(6.0 / 5.0))
    };

    const double weights[10] = {
        2.0,
        1.0, 1.0,
        8.0 / 9.0,
        5.0 / 9.0, 5.0 / 9.0,
        (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0,
        (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0
    };
    GlobalData global;
    const int start_index[4] = { 0, 1, 3, 6 };
    double dN_dksi[GlobalData::npc][4];
    double dN_deta[GlobalData::npc][4];
    double N[GlobalData::npc][4];
    Surface surface[4];
    ElemUniv(GlobalData data);
    ElemUniv();
};
