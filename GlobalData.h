#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

class GlobalData {
public:
    double SimulationTime;
    double SimulationStepTime;
    double Conductivity;
    double Alfa;
    double Tot;
    double InitialTemp;
    double Density;
    double SpecificHeat;
    int nN; // liczba wêz³ów
    int nE; // liczba elementów

    GlobalData(std::ifstream& file);
    void display();
};

