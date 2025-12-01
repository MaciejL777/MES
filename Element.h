#pragma once
#include"ElemUniw.h"
#include"Jakobian.h"
class Node {
public:
    double x, y;
    int BC = 0;
    Node(double xVal, double yVal) : x(xVal), y(yVal) {}
};
class Element :public ElemUniv {
public:
    int ID[4];
    std::vector<Jakobian> J;
    double Hbc[4][4] = { 0 };
    double C_local[4][4] = { 0 };
    double P_local[4] = { 0 };
    Element(int n1, int n2, int n3, int n4, std::vector<Node> nodes);
    double dndx[GlobalData::npc][4];
    double dndy[GlobalData::npc][4];
    double H_local[4][4] = { 0 };
    void Licz_H_P_C(double k, std::vector<Node> nodes, double alfa,double Tot, double density, double specificheat);
};
