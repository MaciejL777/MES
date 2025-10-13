#include "Gauss.h"

Gauss::Gauss(double (*ff1)(double)) : ff1d(ff1) {}
Gauss::Gauss(double (*ff2)(double, double)) : ff2d(ff2) {}

double Gauss::Integrate1d(int num_points) {
    double wynik = 0;
    int start = start_index[num_points - 1];
    for (int i = 0; i < num_points; i++) {
        wynik += ff1d(points[start + i]) * weights[start + i];
    }
    return wynik;
}
double Gauss::Integrate2d(int num_points) {
    double wynik = 0;
    int start = start_index[num_points - 1];
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            wynik += ff2d(points[start + i], points[start + j]) * weights[start + i] * weights[start + j];
        }
    }
    return wynik;
}
void Gauss::SetFunction1d(double (*ff)(double)) {
    ff1d = ff;
}
void Gauss::SetFunction2d(double (*ff)(double,double)) {
    ff2d = ff;
}
double fx(double x) {
    return 5 * pow(x, 2) + 3 * x + 6;
}
double fxy(double x, double y) {
    return 5 * pow(x * y, 2) + 3 * x * y + 6;
}
