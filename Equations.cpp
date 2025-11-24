#include "Equations.h"
Equations::Equations(int nN):size(nN) {
    t.resize(nN);
	P.resize(nN);
	H.resize(nN);
	for (int i = 0; i < nN; i++) {
		H[i].resize(nN);
	}
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
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
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

void Equations::solveSystem()
{
    int n = H.size();
    std::vector<std::vector<double>> A = H;
    std::vector<double> b(n);

    for (int i = 0; i < n; i++)
        b[i] = P[i];

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
            sum -= A[i][j] * t[j];
        t[i] = sum / A[i][i];
    }
}