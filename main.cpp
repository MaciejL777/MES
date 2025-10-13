#include <iostream>
#include <fstream>
#include "GlobalData.h"
#include "Grid.h"
#include "Gauss.h"

using namespace std;

int main() {
    ifstream file("Test1_4_4.txt");
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return 1;
    }

    GlobalData global(file);
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
    cout << "2 punkty: " << funkcja2d.Integrate2d(2) << "\n";
    cout << "3 punkty: " << funkcja2d.Integrate2d(3) << "\n";
    cout << "4 punkty: " << funkcja2d.Integrate2d(4) << "\n";
    
    return 0;
}
