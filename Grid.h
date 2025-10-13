#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GlobalData.h"

class Node {
public:
    double x, y;
    Node(double xVal, double yVal) : x(xVal), y(yVal) {}
};

class Element {
public:
    int ID[4];
    Element(int n1, int n2, int n3, int n4);
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

