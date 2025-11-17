#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

class GlobalData {
public:
    double SimulationTime=0;
    double SimulationStepTime=0;
    double Conductivity=0;
    double Alfa=0;
    double Tot=0;
    double InitialTemp=0;
    double Density=0;
    double SpecificHeat=0;
    int nN=0; // liczba wêz³ów
    int nE=0; // liczba elementów
    const static int npc = 4;
    GlobalData(std::ifstream& file);
    void display();
    GlobalData();
};
class Surface {
public:
    std::vector<std::vector<double>> N;
    void Next(double ksi, double eta);
};
class ElemUniv:public GlobalData {
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
    double dN_dksi[npc][4];
    double dN_deta[npc][4];
    Surface surface[4];
    ElemUniv();
};

