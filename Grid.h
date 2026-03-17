#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GlobalData.h"
#include "Jakobian.h"
#include"Element.h"



class Grid {
public:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::vector<int> BC;
    int nN;
    int nE;
    Grid(std::ifstream& file, const GlobalData& global);
    void display();
};


