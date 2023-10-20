#include "Graph.hpp"

Edge::Edge(int _u, int _v, int _year, int _distance, int _cost){
	u = _u;
	v = _v;
	year = _year;
	distance = _distance;
	cost = _cost;
}


Graph::Graph(int _M){
    M = _M;
    adjList = std::vector<std::vector<Edge*>> (_M + 1);
    parent = std::vector<int>(_M + 1);
    rank = std::vector<int>(_M + 1);
    minDistancesYear = 0;
}


void Graph::addEdge(int u, int v, int year, int distance, int cost){
    Edge *ed1 = new Edge(u, v, year, distance, cost);
	adjList[u].push_back(ed1);
	edges.push_back(ed1);

	Edge *ed2 = new Edge(v, u, year, distance, cost);
	adjList[v].push_back(ed2);
}

std::vector<long long> Graph::getMinDistances(){
    std::vector<long long> minDistances(M + 1, LLONG_MAX);
    std::vector<int> minYear(M + 1, 0);
    minDistances[1] = 0;

    std::priority_queue<PointTo, std::vector<PointTo>, std::greater<PointTo>> pq;
	pq.push({1, 0});

    while(!pq.empty()){
        PointTo current = pq.top();
        pq.pop();

        int U = current.id;
        long long uDistance = current.distance;

        if(uDistance > minDistances[U]) continue;

        for(const Edge *ed : adjList[U]){
            int V = ed->v;
            long long vDistance = ed->distance + uDistance;
            int vYear = ed->year;

            if(vDistance < minDistances[V]){
                minDistances[V] = vDistance;
                pq.push({V, vDistance});

                minYear[V] = vYear;
            }else if(vDistance == minDistances[V]){
                if(vYear < minYear[V]){
                    pq.push({V, vDistance});
                    minYear[V] = vYear;
                }
            }
        }
	}

    for(int i = 2; i <=M;  i++){
        int year = minYear[i];
        if(year > minDistancesYear) minDistancesYear = year;
    }

    return minDistances;
}


int Graph::getMinDistancesYear(){
    return minDistancesYear;
}


void Graph::initTree(){
    for(int i = 1; i <= M; i++){
		parent[i] = i;
		rank[i] = 1; 
	}
}


int Graph::Find(int id, std::vector<int>& parent){
    if (parent[id] == id) return id;
    return parent[id] = Find(parent[id], parent);
}

void Graph::Union(int a, int b, std::vector<int>& parent, std::vector<int>& rank){
    a = Find(a, parent);
    b = Find(b, parent);
    if (a != b){
        if(rank[a] < rank[b]){
            parent[a] = b;
        }else if(rank[a] > rank[b]){
            parent[b] = a;
        }else{
            parent[b] = a;
            rank[a]++;
        }
    }
}


int Graph::getConnectionYear(){
    initTree();
    
    std::sort(edges.begin(), edges.end(), [](const Edge  *a, const Edge  *b) {
        return a->year < b->year;
    });
    
    int connectionYear = 0;

    for (const Edge *ed : edges) {
        int u = ed->u;
        int v = ed->v;
        if(Find(u, parent) != Find(v, parent)) {
            Union(u, v, parent, rank);
            
            if(ed->year > connectionYear) connectionYear = ed->year;
        }
    }
    return connectionYear;
} 


long long Graph::getConnectionCost(){
    initTree();

    std::sort(edges.begin(), edges.end(), [](const Edge  *a, const Edge  *b) {
        return a->cost < b->cost;
    });

    long long totalCost = 0;

    for (const Edge *ed : edges) {
        int u = ed->u;
        int v = ed->v;
        if (Find(u, parent) != Find(v, parent)) {
            Union(u, v, parent, rank);
            totalCost += ed->cost;
        }
    }
    return totalCost;
}