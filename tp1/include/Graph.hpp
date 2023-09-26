#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

class Point{
private:
    int id, degree, nVisited;
    double x, y;
    std::vector<std::pair<int, bool>> neighbors;

public:
    Point(int _id, double _x, double _y, int _d);
    void addNeighbor(int nb);
    double getLineAngle(Point * pt);
    void print();

friend class Graph;
};


class Graph{
private:
    int arcQty, visitedArcs;
    std::vector<Point*> points;
    void recursiveWalk(int id, int prevId, int first, std::vector<int> &face);

public:
    Graph(int edgeQty);
    void addPoint(Point *pt);
    void sortArcs();
    std::vector<std::vector<int>> getFaces();
};

#endif