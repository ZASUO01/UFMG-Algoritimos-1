#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

//Struct used in the Dijkstra priority queue
struct PointTo{
	int id;
	long long distance;

	bool operator>(const PointTo &p2) const {
		return distance > p2.distance;
	}
};


//Graph edges given by the input files
class Edge{
private:
	int u, v, year, distance, cost;

public:
	Edge(int _u, int _v, int _year, int _distance, int _cost);

friend class Graph;
};


//Graph structure to answer the problem questions
class Graph{
private:
    int M;
    int minDistancesYear;
    std::vector<std::vector<Edge*>> adjList;
	std::vector<Edge*> edges;
    std::vector<int> parent;
	std::vector<int> rank;
    void initTree();
    int Find(int id, std::vector<int>& parent);
    void Union(int a, int b, std::vector<int>& parent, std::vector<int>& rank);

public:
    Graph(int _M); 
    void addEdge(int u, int v, int year, int distance, int cost);
    std::vector<long long> getMinDistances(); 
    int getMinDistancesYear();
    int getConnectionYear();
    long long getConnectionCost();
};


#endif