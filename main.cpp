#include <iostream>
#include <fstream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<array>
#include "GlobalData.h"
#include "Grid.h"
#include "Jakobian.h"
#include "Equations.h"
#include"ElemUniw.h"

using namespace std;

int main() {
    ifstream file("Test1_4_4.txt");
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return 1;
    }

    GlobalData global(file);
    ElemUniv elem_univ;
    Grid grid(file, global);
    Equations eq(global.nN);
    eq.Compute_H(grid);
    eq.Compute_P(grid);
    eq.solveSystem();
    std:vector<double> t = eq.getResult();
    global.display();
    grid.display();
    //eq.ShowH();
    cout << "\n";
    for (int i = 0; i < 16; i++) {
        cout <<"Wezel(ID):"<<i+1<<" = "<< t[i] << "\n";
    }
   /* cout << elem_univ.surface[3].N[0][0]<<endl;
    cout << elem_univ.surface[3].N[0][1]<<endl;
    cout << elem_univ.surface[3].N[0][2]<<endl;
    cout << elem_univ.surface[3].N[0][3]<<endl;*/

    /*for (int k = 0; k < GlobalData::npc; k++) {
        cout << "Point" << k << "\n";
        cout << elem_univ.dN_dksi[k][0] << "\n";
        cout << elem_univ.dN_dksi[k][1] << "\n";
        cout << elem_univ.dN_dksi[k][2] << "\n";
        cout << elem_univ.dN_dksi[k][3] << "\n";

        cout << elem_univ.dN_deta[k][0] << "\n";
        cout << elem_univ.dN_deta[k][1] << "\n";
        cout << elem_univ.dN_deta[k][2] << "\n";
        cout << elem_univ.dN_deta[k][3] << "\n";


    };*/
  /* cout << grid.elements[0].J[0].J[0][0] << " " << grid.elements[0].J[0].J[0][1] << " " << grid.elements[0].J[0].J[1][0] << " " << grid.elements[0].J[0].J[1][1] << "\n";
    cout << grid.elements[0].J[1].J[0][0] << " " << grid.elements[0].J[1].J[0][1] << " " << grid.elements[0].J[1].J[1][0] << " " << grid.elements[0].J[1].J[1][1] << "\n";
    cout << grid.elements[0].J[2].J[0][0] << " " << grid.elements[0].J[2].J[0][1] << " " << grid.elements[0].J[2].J[1][0] << " " << grid.elements[0].J[2].J[1][1] << "\n";
    cout << grid.elements[0].J[3].J[0][0] << " " << grid.elements[0].J[3].J[0][1] << " " << grid.elements[0].J[3].J[1][0] << " " << grid.elements[0].J[3].J[1][1] << "\n";*/
    /*double x[4] = { 0.0,0.025,0.025,0.0 };
    double y[4] = { 0.0,0.0,0.025,0.025 };
    Jakobian test(3, x, y);
    cout << test.J[0][0] << " " << test.J[0][1] << " "<<test.J[1][0] << " "<< test.J[1][1];
    cout << "\n" << 1 / test.detJ;*/
    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid.elements[0].Hbc[i][j] << "  ";
        }
        cout << "\n";
    }*/
   
    return 0;
}
