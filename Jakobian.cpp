
#include"Jakobian.h"
Jakobian::Jakobian(int point,double* x,double * y) {
	J[0][0] = dN_dksi[point][0] * x[0] + dN_dksi[point][1] * x[1] + dN_dksi[point][2] * x[2] + dN_dksi[point][3] * x[3];
	J[0][1] = dN_dksi[point][0] * y[0] + dN_dksi[point][1] * y[1] + dN_dksi[point][2] * y[2] + dN_dksi[point][3] * y[3];
	J[1][0] = dN_deta[point][0] * x[0] + dN_deta[point][1] * x[1] + dN_deta[point][2] * x[2] + dN_deta[point][3] * x[3];
	J[1][1] = dN_deta[point][0] * y[0] + dN_deta[point][1] * y[1] + dN_deta[point][2] * y[2] + dN_deta[point][3] * y[3];
	detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
	J1[0][0] = J[1][1]*1/detJ;
	J1[1][1] = J[0][0] * 1 / detJ;
	J1[1][0] =- J[1][0] * 1 / detJ;
	J1[0][1] = -J[0][1] * 1 / detJ;
}