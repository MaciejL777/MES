#include "Grid.h"
#include "Jakobian.h"
#include<array>
Element::Element(int n1, int n2, int n3, int n4,std::vector<Node> nodes,double k) {
    ID[0] = n1; ID[1] = n2; ID[2] = n3; ID[3] = n4;
    
    double x[4] = { nodes[n1-1].x,nodes[n2-1].x,nodes[n3-1].x,nodes[n4-1].x };
    double y[4] = { nodes[n1-1].y,nodes[n2-1].y,nodes[n3-1].y,nodes[n4-1].y };
     for (int i =  0; i < npc; i++) {
            Jakobian jk(i,x,y);
            J.push_back(jk);
    }
     
     Licz_H(k);
}
void Element::Licz_H(double k) {

    for (int i = 0; i < npc; i++) {
        for (int j = 0; j < 4; j++) {
            dndx[i][j] = J[i].J1[0][0] * dN_dksi[i][j] + J[i].J1[0][1] * dN_deta[i][j];
            dndy[i][j] = J[i].J1[1][0] * dN_dksi[i][j] + J[i].J1[1][1] * dN_deta[i][j];
        }
    }

    std::array<std::array<double, 4>, 4> wynik{};
    std::vector<std::array<std::array<double, 4>, 4>> Hpc;

    for (int n = 0; n < npc; n++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                double v = (dndx[n][i] * dndx[n][j] + dndy[n][i] * dndy[n][j]) *(double)k * J[n].detJ;
                wynik[i][j] = v;
              /* std:: cout <<"v:"<< v << "\n";
               std::cout << "dndx:" << dndx[n][i]<<"   "<<dndx[n][j] << "\n";
               std::cout << "dndy:" << dndy[n][i] << "   " << dndy[n][j] << "\n";
               std::cout << "detJ:" << J[n].detJ << "\n";
               std::cout << "conductivity:" << k << "\n";*/
            }
        }
        Hpc.push_back(wynik);
    }

    int num_points = static_cast<int>(sqrt(npc));
    int start = start_index[num_points - 1];
    std::vector<double> w;
    for (int i = num_points-1; i >=0; i--) {
        for (int j = num_points-1; j >=0; j--) {
            w.push_back(weights[start + i] * weights[start + j]);
        }
    } 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
             for (int n = 0; n < npc; n++) {
                     H_local[i][j] += Hpc[n][i][j] * w[n];
             }
             
        }
    }
}


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
        elements.emplace_back(n1, n2, n3, n4,nodes,global.Conductivity);
    }

    while (std::getline(file, line)) {
        if (line.find("*BC") != std::string::npos) break;
    }

    if (std::getline(file, line)) {
        for (char& c : line) if (c == ',') c = ' ';
        std::istringstream iss(line);
        int val;
        while (iss >> val) BC.push_back(val);
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