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
void Surface::Next(double ksi, double eta) {
    std::vector<double> pc;
    pc.push_back( 0.25 * (1 - ksi) * (1 - eta));
    pc.push_back(0.25 * (1 + ksi) * (1 - eta));
    pc.push_back(0.25 * (1 + ksi) * (1 + eta));
    pc.push_back(0.25 * (1 - ksi) * (1 + eta));
    N.push_back(pc);
}
ElemUniv::ElemUniv() {
    int numpoints = sqrt(npc);
    int k = 0;
    int start = start_index[numpoints -1];
        for (int j = numpoints-1; j >=0; j--) {
            for (int i = numpoints-1; i>=0; i--) {
                dN_dksi[k][0] = -0.25 * (1 - points[start + j]);
                dN_dksi[k][1] = 0.25 * (1 - points[start + j]);
                dN_dksi[k][2] = 0.25 * (1 + points[start + j]);
                dN_dksi[k][3] = -0.25 * (1 + points[start + j]);

                dN_deta[k][0] = -0.25 * (1 - points[start + i]);
                dN_deta[k][1] = -0.25 * (1 + points[start + i]);
                dN_deta[k][2] = 0.25 * (1 + points[start + i]);
                dN_deta[k][3] = 0.25 * (1 - points[start + i]);

                k++;
            }
        }
        Surface dol;
        for (int i=0; i <numpoints; i++) {
            dol.Next(points[start + i], -1);
        }
        surface[0] = dol;
        Surface prawo;
        for (int i=0; i < numpoints; i++) {
            prawo.Next(1, points[start + i]);
        }
        surface[1] = prawo;
        Surface gora;
        for (int i = 0 ; i < numpoints; i++) {
            gora.Next(points[start + i], 1);
        }
        surface[2] = gora;
        Surface lewo;
        for (int i = 0; i < numpoints; i++) {
            lewo.Next(-1, points[start+i]);
        }
        surface[3] = lewo;
}

