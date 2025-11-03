#pragma once
#include<vector>
#include"Grid.h"
class Equations
{
public:
	int size;
	std::vector<std::vector<double>> H;
	void Compute_H(Grid grid);
	Equations(int nN);
};

