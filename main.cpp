#include <iostream>
#include <fstream>
#include<vector>
#include "GlobalData.h"
#include "Grid.h"
#include "Gauss.h"
#include "Jakobian.h"

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

    global.display();
    grid.display();

    Gauss funkcja1d(fx);
    cout << "\n=== Integracja Gaussa ===" << endl;
    cout << "1 punkt: " << funkcja1d.Integrate1d(1) << "\n";
    cout << "2 punkty: " << funkcja1d.Integrate1d(2) << "\n";
    cout << "3 punkty: " << funkcja1d.Integrate1d(3) << "\n";
    cout << "4 punkty: " << funkcja1d.Integrate1d(4) << "\n";
    Gauss funkcja2d(fxy);
    cout << "\n=== Integracja Gaussa ===" << endl;
    cout << "1 punkt: " << funkcja2d.Integrate2d(1) << "\n";
    cout << "2 punkty: " << funkcja2d.Integrate2d(4) << "\n";
    cout << "3 punkty: " << funkcja2d.Integrate2d(9) << "\n";
    cout << "4 punkty: " << funkcja2d.Integrate2d(16) << "\n";
    
    for (int k = 0; k < GlobalData::npc; k++) {
        cout << "Point" << k << "\n";
            cout << elem_univ.dN_dksi[k][0] << "\n";
            cout << elem_univ.dN_dksi[k][1] << "\n";
            cout << elem_univ.dN_dksi[k][2] << "\n";
            cout << elem_univ.dN_dksi[k][3] << "\n";

            cout << elem_univ.dN_deta[k][0] << "\n";
            cout << elem_univ.dN_deta[k][1] << "\n";
            cout << elem_univ.dN_deta[k][2] << "\n";
            cout << elem_univ.dN_deta[k][3] << "\n";
          
        
    }
   /* cout << grid.elements[0].J[0].J[0][0] << " " << grid.elements[0].J[0].J[0][1] << " " << grid.elements[0].J[0].J[1][0] << " " << grid.elements[0].J[0].J[1][1] << "\n";
    cout << grid.elements[0].J[1].J[0][0] << " " << grid.elements[0].J[1].J[0][1] << " " << grid.elements[0].J[1].J[1][0] << " " << grid.elements[0].J[1].J[1][1] << "\n";
    cout << grid.elements[0].J[2].J[0][0] << " " << grid.elements[0].J[2].J[0][1] << " " << grid.elements[0].J[2].J[1][0] << " " << grid.elements[0].J[2].J[1][1] << "\n";
    cout << grid.elements[0].J[3].J[0][0] << " " << grid.elements[0].J[3].J[0][1] << " " << grid.elements[0].J[3].J[1][0] << " " << grid.elements[0].J[3].J[1][1] << "\n";*/
    double x[4] = { 0.0,0.025,0.025,0.0 };
    double y[4] = { 0.0,0.0,0.025,0.025 };
    Jakobian test(3, x, y);
    cout << test.J[0][0] << " " << test.J[0][1] << " "<<test.J[1][0] << " "<< test.J[1][1];
    cout << "\n" << 1 / test.detJ;
    return 0;
}
