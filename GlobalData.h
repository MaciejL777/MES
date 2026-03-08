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
    const static int npc = 16;
    GlobalData(std::ifstream& file);
    void display();
    GlobalData();
};


