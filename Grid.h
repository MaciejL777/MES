#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GlobalData.h"
#include "Gauss.h"
#include "Jakobian.h"

class Node {
public:
    double x, y;
    Node(double xVal, double yVal) : x(xVal), y(yVal) {}
};
class Element :public ElemUniv {
public:
    int ID[4];
    std::vector<Jakobian> J;
    Element(int n1, int n2, int n3, int n4,std::vector<Node> nodes,double k);
    double dndx[GlobalData::npc][4];
    double dndy[GlobalData::npc][4];
    double H_local[4][4] = {0};
    void Licz_H(double k);
};

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


