#include"ElemUniw.h"
#include<cmath>
ElemUniv::ElemUniv(GlobalData data) {
    global = data;
    int numpoints = sqrt(global.npc);
    int k = 0;
    int start = start_index[numpoints - 1];
    for (int j = numpoints - 1; j >= 0; j--) {
        for (int i = numpoints - 1; i >= 0; i--) {
            dN_dksi[k][0] = -0.25 * (1 - points[start + j]);
            dN_dksi[k][1] = 0.25 * (1 - points[start + j]);
            dN_dksi[k][2] = 0.25 * (1 + points[start + j]);
            dN_dksi[k][3] = -0.25 * (1 + points[start + j]);

            dN_deta[k][0] = -0.25 * (1 - points[start + i]);
            dN_deta[k][1] = -0.25 * (1 + points[start + i]);
            dN_deta[k][2] = 0.25 * (1 + points[start + i]);
            dN_deta[k][3] = 0.25 * (1 - points[start + i]);

            N[k][0] = 0.25 * (1 - points[start + i]) * (1 - points[start + j]);
            N[k][1] = 0.25 * (1 + points[start + i]) * (1 - points[start + j]);
            N[k][2] = 0.25 * (1 + points[start + i]) * (1 + points[start + j]);
            N[k][3] = 0.25 * (1 - points[start + i]) * (1 + points[start + j]);
            k++;
        }
    }
    Surface dol;
    for (int i = 0; i < numpoints; i++) {
        dol.Next(points[start + i], -1);
    }
    surface[0] = dol;
    Surface prawo;
    for (int i = 0; i < numpoints; i++) {
        prawo.Next(1, points[start + i]);
    }
    surface[1] = prawo;
    Surface gora;
    for (int i = 0; i < numpoints; i++) {
        gora.Next(points[start + i], 1);
    }
    surface[2] = gora;
    Surface lewo;
    for (int i = 0; i < numpoints; i++) {
        lewo.Next(-1, points[start + i]);
    }
    surface[3] = lewo;
}
void Surface::Next(double ksi, double eta) {
    std::vector<double> pc;
    pc.push_back(0.25 * (1 - ksi) * (1 - eta));
    pc.push_back(0.25 * (1 + ksi) * (1 - eta));
    pc.push_back(0.25 * (1 + ksi) * (1 + eta));
    pc.push_back(0.25 * (1 - ksi) * (1 + eta));
    N.push_back(pc);
}
