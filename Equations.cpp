#include "Equations.h"
Equations::Equations(int nN):size(nN) {
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