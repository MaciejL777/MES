#pragma once
#include<vector>
#include<iostream>
#include<iomanip>
#include"Grid.h"
class Equations
{
public:
	int size;
	std::vector<std::vector<double>> H;
	std::vector<double> P;
	std::vector<double> t;
	void Compute_H(Grid grid);
	void Compute_P(Grid grid);
	void solveSystem();
	std::vector<double> getResult() {
		return t;
	}
	Equations(int nN);
	void ShowH(); 
};

