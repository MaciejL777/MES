#pragma once
#include<vector>
#include<iostream>
#include<iomanip>
#include"Grid.h"
class Equations
{
public:
	int size;
	double dt;
	std::vector<std::vector<double>> H;
	std::vector<std::vector<double>> C;
	std::vector<std::vector<double>> HC;
	std::vector<double> P;
	std::vector<double> PC;
	std::vector<double> t1;
	std::vector<double> t0;
	void Compute_H(const Grid& grid);
	void Compute_P(const Grid& grid);
	void Compute_C(const Grid& grid);
	void Compute_HC();
	void Compute_PC();
	void Compute(const Grid& grid);
	void solveSystem();
	std::vector<double> getResult() {
		return t1;
	}
	Equations(int nN,double Initialtemp,double t);
	void ShowH(); 
	void ShowC();
};

