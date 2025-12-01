#include "Grid.h"
#include "Jakobian.h"
#include<array>


Grid::Grid(std::ifstream& file, const GlobalData& global) : nN(global.nN), nE(global.nE) {
    std::string line;
    file.seekg(0, std::ios::beg);
    while (std::getline(file, line)) {
        if (line.find("*Node") != std::string::npos) break;
    }

    nodes.reserve(nN);
    for (int i = 0; i < nN; ++i) {
        std::string line;
        if (!std::getline(file, line)) {
            std::cerr << "Blad: oczekiwano wiecej wezlow" << std::endl;
            exit(1);
        }

        for (char& c : line) if (c == ',') c = ' ';
        std::istringstream iss(line);
        int id;
        double x, y;
        if (!(iss >> id >> x >> y)) {
            std::cerr << "Blad przy wczytywaniu wezla nr " << i + 1 << " | linia: " << line << std::endl;
            exit(1);
        }
        nodes.emplace_back(x, y);
    }

    while (std::getline(file, line)) {
        if (line.find("*Element") != std::string::npos) break;
    }

    elements.reserve(nE);
    for (int i = 0; i < nE; ++i) {
        std::string line;
        if (!std::getline(file, line)) {
            std::cerr << "oczekiwano wiecej elementow" << std::endl;
            exit(1);
        }

        for (char& c : line) if (c == ',') c = ' ';
        std::istringstream iss(line);

        int id, n1, n2, n3, n4;
        if (!(iss >> id >> n1 >> n2 >> n3 >> n4)) {
            std::cerr << "blad przy wczytywaniu elementu nr " << i + 1 << " | linia: " << line << std::endl;
            exit(1);
        }
        //std::cout << tmp[0].x << " " << tmp[1].x << " " << tmp[2].x << " " << tmp[3].x << "\n";
        //std::cout << tmp[0].y << " " << tmp[1].y << " " << tmp[2].y << " " << tmp[3].y << "\n";
        elements.emplace_back(n1, n2, n3, n4,nodes);
    }

    while (std::getline(file, line)) {
        if (line.find("*BC") != std::string::npos) break;
    }

    if (std::getline(file, line)) {
        for (char& c : line) if (c == ',') c = ' ';
        std::istringstream iss(line);
        int val;
        while (iss >> val) {
            BC.push_back(val);
            nodes[val - 1].BC = 1;
        }
    }
    for (int i = 0; i < nE;i++) {
        elements[i].Licz_H_P_C(global.Conductivity, nodes,global.Alfa,global.Tot,global.Density,global.SpecificHeat);
    }
}
void Grid::display()  {
    std::cout << std::fixed;
    std::cout.precision(11);

    std::cout << "\n=== Nodes (ID, x, y) ===" << std::endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << i + 1 << ": x = " << nodes[i].x
            << ", y = " << nodes[i].y << std::endl;
    }

    std::cout << "\n=== Elements (ID wezlow) ===" << std::endl;
    for (size_t i = 0; i < elements.size(); i++) {
        std::cout << "Element " << i + 1 << ": ";
        for (int j = 0; j < 4; ++j)
            std::cout << elements[i].ID[j] << " ";
        std::cout << std::endl;
    }

    std::cout << "\n=== Warunki brzegowe (BC) ===" << std::endl;
    for (int b : BC) std::cout << b << " ";
    std::cout << std::endl;
}