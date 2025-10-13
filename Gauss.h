#pragma once

#include <cmath>

class Gauss {
    double (*ff1d)(double) = nullptr;
    double (*ff2d)(double, double) = nullptr;
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

    const int start_index[4] = { 0, 1, 3, 6 };
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
