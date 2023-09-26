#include "Graph.hpp"

int main(int argc, char *argv[]){
    int m, n, d, i, j, nb;
    double x, y;

    std::cin >> m >> n;
    
    Graph *graph = new Graph(n);

    for(i = 0; i < m; i++){
        std::cin >> x >> y >> d;

        Point * pt = new Point(i + 1, x, y, d);
        for(j = 0; j < d; j++){
            std::cin >> nb;
            pt->addNeighbor(nb);
        }
        graph->addPoint(pt);
    }
    
    graph->sortArcs();
    std::vector<std::vector<int>> faces = graph->getFaces();
    
    int size = faces.size();
    std::cout << size << std::endl;
    for(i = 0; i < size; i++){
        std::vector<int> face = faces[i];
        int fSize = face.size();
        std::cout << fSize << " ";
        for(j = 0; j < fSize; j++){
            std::cout << face[j];
            if(j != fSize - 1){
                std::cout << " ";
            }else{
                std::cout << std::endl;
            }
        }
    }
    
    return 0;
}