#include "Equations.h"
Equations::Equations(int nN,double Initialtemp,double t):size(nN) {
    t1.resize(nN);
    t0.resize(nN);
	P.resize(nN);
    PC.resize(nN);
	H.resize(nN);
    HC.resize(nN);
    C.resize(nN);
	for (int i = 0; i < nN; i++) {
		H[i].resize(nN);
        HC[i].resize(nN);
        C[i].resize(nN);
        t0[i]=Initialtemp;
	}
    dt = t;
}
void Equations::Compute_H(Grid grid) {
	for (int ID = 0; ID < grid.nE; ID++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				H[grid.elements[ID].ID[i]-1][grid.elements[ID].ID[j]-1] += grid.elements[ID].H_local[i][j];
			}
		}
	}
}
void Equations::ShowH() {
	std::cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << H[i][j] << "  ";
		}
		std::cout << "\n";
	}
}
void Equations::Compute_P(Grid grid){
	for (int ID = 0; ID < grid.nE; ID++) {
		for (int i = 0; i < 4; i++) {
				P[grid.elements[ID].ID[i] - 1] += grid.elements[ID].P_local[i];
		}
	}
}
void Equations::Compute_C(Grid grid) {
    for (int ID = 0; ID < grid.nE; ID++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                C[grid.elements[ID].ID[i] - 1][grid.elements[ID].ID[j] - 1] += grid.elements[ID].C_local[i][j];
            }
        }
    }
}
void Equations::ShowC() {
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << C[i][j] << "  ";
        }
        std::cout << "\n";
    }
}
void Equations::Compute_HC() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            HC[i][j] = H[i][j] + (C[i][j] / dt);
        }
    }
}
void Equations::Compute_PC() {
    fill(PC.begin(), PC.end(), 0);
    for (int i = 0; i < size; i++) {
        PC[i] += P[i];
        for (int j = 0; j < size; j++) {
            PC[i]+= (C[i][j] * t0[j] / dt);
        }
    }
}
void Equations::Compute(Grid grid) {
    Compute_H(grid);
    Compute_P(grid);
    Compute_C(grid);
    Compute_HC();
}

void Equations::solveSystem()
{
    Compute_PC();
    int n = HC.size();
    std::vector<std::vector<double>> A = HC;
    std::vector<double> b(n);

    for (int i = 0; i < n; i++)
        b[i] = PC[i];

    for (int i = 0; i < n; i++) {
        double maxEl = std::abs(A[i][i]);
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > maxEl) {
                maxEl = std::abs(A[k][i]);
                pivot = k;
            }
        }

        std::swap(A[i], A[pivot]);
        std::swap(b[i], b[pivot]);

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    
    for (int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < n; j++)
            sum -= A[i][j] * t1[j];
        t1[i] = sum / A[i][i];
    }
}