#include "GlobalData.h"
#include "Gauss.h"

GlobalData::GlobalData(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line.find("*Node") != std::string::npos) break;

        std::istringstream iss(line);
        std::string key, tmp;

        iss >> key;

        if (key == "SimulationTime") { iss >> SimulationTime; }
        else if (key == "SimulationStepTime") { iss >> SimulationStepTime; }
        else if (key == "Conductivity") { iss >> Conductivity; }
        else if (key == "Alfa") { iss >> Alfa; }
        else if (key == "Tot") { iss >> Tot; }
        else if (key == "InitialTemp") { iss >> InitialTemp; }
        else if (key == "Density") { iss >> Density; }
        else if (key == "SpecificHeat") { iss >> SpecificHeat; }
        else if (key == "Nodes") { iss >> tmp >> nN; }
        else if (key == "Elements") { iss >> tmp >> nE; }
    }

    if (nN <= 0 || nN > 10000) {
        std::cerr << "Blad: nieprawidlowa liczba wezlow (" << nN << ")" << std::endl;
        exit(1);
    }
    if (nE <= 0 || nE > 10000) {
        std::cerr << "Blad: nieprawidlowa liczba elementow (" << nE << ")" << std::endl;
        exit(1);
    }
}
void GlobalData::display()  {
    std::cout << "=== Dane globalne ===" << std::endl;
    std::cout << "SimulationTime = " << SimulationTime << std::endl;
    std::cout << "SimulationStepTime = " << SimulationStepTime << std::endl;
    std::cout << "Conductivity = " << Conductivity << std::endl;
    std::cout << "Alfa = " << Alfa << std::endl;
    std::cout << "Tot = " << Tot << std::endl;
    std::cout << "InitialTemp = " << InitialTemp << std::endl;
    std::cout << "Density = " << Density << std::endl;
    std::cout << "SpecificHeat = " << SpecificHeat << std::endl;
    std::cout << "Liczba wezlow = " << nN << ", Liczba elementow = " << nE << std::endl;
}
GlobalData::GlobalData() {}



