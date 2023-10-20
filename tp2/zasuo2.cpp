#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;


class Edge{
private:
	

public:
	int u, v, year, distance, cost;
	Edge(int _u, int _v, int _year, int _distance, int _cost);
};

Edge::Edge(int _u, int _v, int _year, int _distance, int _cost){
	u = _u;
	v = _v;
	year = _year;
	distance = _distance;
	cost = _cost;
}

struct PointTo{
	int id;
	long long distance;

	bool operator>(const PointTo &p2) const {
		return distance > p2.distance;
	}
};

int Find(int id, vector<int>& parent) {
    if (parent[id] == id) return id;
    return parent[id] = Find(parent[id], parent);
}

void Union(int a, int b, vector<int>& parent, vector<int>& rank) {
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

int yearBinarySearch(vector<Edge*> &eds, int u, int v){
    int left = 0;
    int right = eds.size() - 1;
    
    while (left <= right) {
        int middle = left + (right - left) / 2;
 
        Edge *ed = eds[middle];

        if (ed->u == u){
            if(ed->v == v) return ed->year;
            else if(ed->v < v) left = middle + 1;
            else right = middle - 1;
        }
        else if(ed->u < u) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}



int main(){
	int M, N, i;
	cin >> M >> N;

	// Create adj List
	vector<vector<Edge*>> adjList(M + 1);
	vector<Edge*> edges;

	int u, v, year, distance, cost;
	for(i = 0; i < N; i++){
		cin >> u >> v >> year >> distance >> cost;
		Edge *ed1 = new Edge(u, v, year, distance, cost);
		adjList[u].push_back(ed1);
		edges.push_back(ed1);

		Edge *ed2 = new Edge(v, u, year, distance, cost);
		adjList[v].push_back(ed2);
	}

	// Get min distances
	vector<long long> minDistances(M + 1, LLONG_MAX);
    vector<int> minYear(M + 1, 0);

    minDistances[1] = 0;

	priority_queue<PointTo, vector<PointTo>, greater<PointTo>> pq;
	pq.push({1, 0});

	int minDistancesYear = 0;

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

    
	//print min distances
	for(i = 1; i <= M ; i++){
		cout << minDistances[i] << endl;
	}

	//print minimum path stability time
    for(int i = 2; i <=M;  i++){
        int year = minYear[i];
        if(year > minDistancesYear) minDistancesYear = year;
    }
    cout << minDistancesYear << endl;

	// Get minimum spaning trees

	vector<int> parent(M + 1);
	vector<int> rank(M + 1);

	for(i = 1; i <= M; i++){
		parent[i] = i;
		rank[i] = 1; 
	}

	sort(edges.begin(), edges.end(), [](const Edge  *a, const Edge  *b) {
        return a->year < b->year;
    });

	long long connectionYear = 0;

    for (const Edge *ed : edges) {
        int u = ed->u;
        int v = ed->v;
        if(Find(u, parent) != Find(v, parent)) {
            Union(u, v, parent, rank);
            
            if(ed->year > connectionYear) connectionYear = ed->year;
        }
    }

	//The first year in which the kingdom is connected
	cout << connectionYear << endl;

	for(i = 1; i <= M; i++){
		parent[i] = i;
		rank[i] = 1; 
	}

	sort(edges.begin(), edges.end(), [](const Edge  *a, const Edge  *b) {
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

	// The minimum cost to get the kingdom connected
	cout << totalCost << endl;
    
	return 0;
}