#pragma once
#include"Element.h"
#include<array>
Element::Element(int n1, int n2, int n3, int n4, std::vector<Node> nodes) {
    ID[0] = n1; ID[1] = n2; ID[2] = n3; ID[3] = n4;

    double x[4] = { nodes[n1 - 1].x,nodes[n2 - 1].x,nodes[n3 - 1].x,nodes[n4 - 1].x };
    double y[4] = { nodes[n1 - 1].y,nodes[n2 - 1].y,nodes[n3 - 1].y,nodes[n4 - 1].y };
    for (int i = 0; i < GlobalData::npc; i++) {
        Jakobian jk(i, x, y);
        J.push_back(jk);
    }
}
void Element::Licz_H_P_C(double k, std::vector<Node> nodes, double alfa,double Tot,double density, double specificheat) {
   // if (nodes[ID[1] - 1].BC == 1 && nodes[ID[(1 + 1) % 4] - 1].BC == 1) {////////Zmiana temperatury startowej po prawej stronie
     //   Tot = 200;                                                        /////////////
    //}                                                                  /////////////////////////////
    for (int i = 0; i < GlobalData::npc; i++) {
        for (int j = 0; j < 4; j++) {
            dndx[i][j] = J[i].J1[0][0] * Univ->dN_dksi[i][j] + J[i].J1[0][1] * Univ->dN_deta[i][j];
            dndy[i][j] = J[i].J1[1][0] * Univ->dN_dksi[i][j] + J[i].J1[1][1] * Univ->dN_deta[i][j];
        }
    }

    std::array<std::array<double, 4>, 4> wynik{};
    std::vector<std::array<std::array<double, 4>, 4>> Hpc;
    std::array<std::array<double, 4>, 4> wynikC{};
    std::vector<std::array<std::array<double, 4>, 4>> Cpc;

    for (int n = 0; n < GlobalData::npc; n++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                double v = (dndx[n][i] * dndx[n][j] + dndy[n][i] * dndy[n][j]) * (double)k * J[n].detJ;
                double c = density * specificheat * Univ->N[n][i] * Univ->N[n][j] * J[n].detJ;
                wynik[i][j] = v;
                wynikC[i][j] = c;
                /* std:: cout <<"v:"<< v << "\n";
                 std::cout << "dndx:" << dndx[n][i]<<"   "<<dndx[n][j] << "\n";
                 std::cout << "dndy:" << dndy[n][i] << "   " << dndy[n][j] << "\n";
                 std::cout << "detJ:" << J[n].detJ << "\n";
                 std::cout << "conductivity:" << k << "\n";*/
            }
        }
        Hpc.push_back(wynik);
        Cpc.push_back(wynikC);
    }

    int num_points = static_cast<int>(sqrt(GlobalData::npc));
    int start = Univ->start_index[num_points - 1];
    std::vector<double> w;
    for (int i = num_points - 1; i >= 0; i--) {
        for (int j = num_points - 1; j >= 0; j--) {
            w.push_back(Univ->weights[start + i] * Univ->weights[start + j]);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int n = 0; n < GlobalData::npc; n++) {
                H_local[i][j] += Hpc[n][i][j] * w[n];
                C_local[i][j] += Cpc[n][i][j] * w[n];
            }

        }
    }
    for (int bok = 0; bok < 4; bok++) {
        if (nodes[ID[bok] - 1].BC == 1 && nodes[ID[(bok + 1) % 4] - 1].BC == 1) {
            double dy = abs(nodes[ID[bok] - 1].y - nodes[ID[(bok + 1) % 4] - 1].y);
            double dx = abs(nodes[ID[bok] - 1].x - nodes[ID[(bok + 1) % 4] - 1].x);
            double detJ = sqrt(dy * dy + dx * dx) / 2.0;
            for (int n = 0; n < num_points; n++) {
                for (int i = 0; i < 4; i++) {
                    P_local[i] += alfa * Univ->surface[bok].N[n][i] * Univ->weights[start + n] * detJ*Tot;
                    for (int j = 0; j < 4; j++) {
                        Hbc[i][j] += alfa * Univ->surface[bok].N[n][i] * Univ->surface[bok].N[n][j] * Univ->weights[start + n] * detJ;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            H_local[i][j] += Hbc[i][j];
        }
    }
}