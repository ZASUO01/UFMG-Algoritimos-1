#include "Graph.hpp"


int main(){
    int M, N, i;
    std::cin >> M >> N;

    Graph graph(M);
    int u, v, year, distance, cost;
    
    for(i = 0; i < N; i++){
        std::cin >> u >> v >> year >> distance >> cost;
        graph.addEdge(u, v, year, distance, cost);
    }

    std::vector<long long> minDistances = graph.getMinDistances();
    int minDistancesYear = graph.getMinDistancesYear();
    int connectionYear = graph.getConnectionYear();
    long long connectionCost = graph.getConnectionCost();

    //Minimum distances to origin to each village
    for(i = 1; i <= M ; i++){
		std::cout << minDistances[i] << std::endl;
	}

    //The first year which all minimum distances are reachable
    std::cout << minDistancesYear << std::endl;

    //The first year which the kingdom is connected
    std::cout << connectionYear << std::endl;

    //The minimum cost to get the kingdom is connected
    std::cout << connectionCost << std::endl;

    return 0;
}