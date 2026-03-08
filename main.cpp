#include <iostream>
#include <fstream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<array>
#include <chrono>
#include <cstdlib>
#include <string>
#include "GlobalData.h"
#include "Grid.h"
#include "Jakobian.h"
#include "Equations.h"
#include"ElemUniw.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;
ElemUniv* Jakobian::Univ = nullptr;
ElemUniv* Element::Univ = nullptr;
int main(int argc, char** argv) {
    // start pomiaru czasu od wejścia do main
    auto t_start = std::chrono::high_resolution_clock::now();

    int numThreads = 0;
    if (argc > 1) {
        try {
            numThreads = std::stoi(argv[1]);
        } catch (...) {
            numThreads = 0;
        }
    }
    if (numThreads <= 0) {
        char* env = nullptr;
        size_t envLen = 0;
        if (_dupenv_s(&env, &envLen, "OMP_NUM_THREADS") == 0 && env != nullptr) {
            try {
                numThreads = std::stoi(env);
            } catch (...) {
                numThreads = 0;
            }
        }
    }

#ifdef _OPENMP
    if (numThreads > 0) {
        omp_set_num_threads(numThreads);
    }
    int used = omp_get_max_threads();
    cout << "OpenMP dostępne. Liczba watkow ustawiona na: " << used << "\n";
#else
    if (numThreads > 0) {
        cout << "Uwaga: program skompilowany bez OpenMP. Ignoruje ustawienie liczby wątkow.\n";
    } else {
        cout << "OpenMP niedostepne.\n";
    }
#endif

    ifstream file("Test3_31_31_kwadrat.txt");
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return 1;
    }
    vector<Node> wyniki;
    GlobalData global(file);
    ElemUniv elem_univ(global);
    Jakobian::setUniv(&elem_univ);
    Element::setUniv(&elem_univ);
    Grid grid(file, global);
    Equations eq(global.nN,global.InitialTemp,global.SimulationStepTime);
    eq.Compute(grid);
    global.display();
    grid.display();
    for (int j = 0; j < global.SimulationTime/global.SimulationStepTime; j++) {
        eq.solveSystem();
        std::vector<double> t = eq.getResult();
        eq.t0 = t;
        cout << "Iteracja: " << j+1 << "\n";
        Node min_max(global.InitialTemp,global.InitialTemp);
        min_max.x = t[0];
        min_max.y = t[0];
        for (int i = 0; i < global.nN; i++) {
            if (t[i] < min_max.x) {
                min_max.x = t[i];
            }
            else if (t[i] > min_max.y) {
                min_max.y = t[i];
            }
            cout << "Wezel(ID):" << i + 1 << " = " << t[i] << "\n";
        }
        wyniki.push_back(min_max);
    }
    for (int i = 0; i < global.SimulationTime / global.SimulationStepTime; i++) {
        cout << "Min: " << wyniki[i].x << "     Max: " << wyniki[i].y << "    Czas: "<<(int)global.SimulationStepTime*(i+1)<<"s"<<endl;
    }

    // koniec pomiaru czasu i wypis
    auto t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = t_end - t_start;
    cout << "Calkowity czas wykonania programu: " << elapsed.count() << " s\n";

    return 0;
}
