#include "Graph.hpp"

Point::Point(int _id, double _x, double _y, int _d){
    id = _id;
    x = _x;
    y = _y;
    degree = _d;
    nVisited = 0;
}


void Point::addNeighbor(int nb){
    std::pair<int, bool> edge = {nb, false};
    neighbors.push_back(edge);
}

//Returns the angle made with 2 points in degrees [0, 360]
double Point::getLineAngle(Point * pt){
    double radians = atan2((pt->y - y), (pt->x - x));
    double degrees = radians * (180 / M_PI);
    if(degrees < 0){
       return degrees + 360;
    }else return degrees;
}


void Point::print(){
    int size = neighbors.size(); 
    std::cout << "ID: " << id << "(" << x << "," << y << ")";
    if(size == degree){
        std::cout << " [ ";
        for(int i = 0; i < degree; i++){
            std::cout << neighbors[i].first << " ";
        }
        std::cout << "]" << std::endl;
    }else std::cout << std::endl;
}


Graph::Graph(int edgeQty){
    arcQty = 2 * edgeQty;
    visitedArcs = 0;
}


void Graph::addPoint(Point *pt){
    points.push_back(pt);
}

//For each point, it sorts the its neighbor list by the clockwise order of angles
void Graph::sortArcs(){
    int i, j;
    std::vector<std::pair<int, double>> tempN;
    
    int size = points.size();
    for(i = 0; i < size; i++){
        Point *p1 = points[i];
        
        int nSize = p1->degree;
        
        for(j = 0; j < nSize; j++){
            int nb = p1->neighbors[j].first;
            
            Point *p2 = points[nb - 1];
            double angle = p1->getLineAngle(p2);
            
            std::pair<int, double> edge;
            edge.first = nb;
            edge.second = angle;
            
            tempN.push_back(edge);
        }

        std::sort(tempN.begin(), tempN.end(),
        [](std::pair<int, double> p1, std::pair<int, double> p2){
            if(p1.second > p2.second) return true;
            return false;
        });

        for(j = 0; j < nSize; j++){
            p1->neighbors[j].first = tempN[j].first;
        }
        
        tempN.clear();
    }
}


void Graph::recursiveWalk(int id, int prevId, int first, std::vector<int> &face){
    int i, nSize, nextId;
    Point * current = points[id - 1];

    face.push_back(current->id);

    nSize = current->degree;

    //Stop condition. If the walk returned to the
    //starter point and there's no next unvisited neighbor, stop the recursion
    if(current->id == first){
        int arcCounter = 0;

        for(i = 0; i < nSize; i++){
            std::pair<int, bool> nb = current->neighbors[i];
            if(nb.first == prevId){
                std::pair<int, bool> next;
                if(i == nSize - 1) next = current->neighbors[0];
                else next = current->neighbors[i+1];
                
                if(!next.second) arcCounter++;
            }
        }
        if(arcCounter == 0){
            return;
        }
    }
    
    //It goes to the parent point in the walk
    //Look in the neighbors list for this point
    //Take the next point
    for(i = 0; i < nSize; i++){
        int currentPrevID = current->neighbors[i].first;
        
        if((currentPrevID == prevId)){
            if(i == nSize - 1){
                nextId = current->neighbors[0].first;
                current->neighbors[0].second = true;
                visitedArcs++;
            }else{
                nextId = current->neighbors[i+1].first;
                current->neighbors[i+1].second = true;
                visitedArcs++;
                i = nSize - 1;
            }
        }
    }

    //Visit this arc and go to the next  
    current->nVisited++;
    recursiveWalk(nextId, current->id, first, face);
}

//It returns a list containing all faces of the graph
std::vector<std::vector<int>> Graph::getFaces(){
    int i, j, nSize;
    int size = points.size();
    std::vector<std::vector<int>> faces;

    //take a point to start the walk from
    for(i = 0; i < size; i++){
        Point *start = points[i];
        nSize = start->degree;

        std::vector<int> face;
        for(j = 0; j < nSize; j++){
            bool visited = start->neighbors[j].second;
            if(!visited){
                start->neighbors[j].second = true;
        
                visitedArcs++;
                start->nVisited++;

                int nb = start->neighbors[j].first;
                
                face.push_back(start->id);
                
                recursiveWalk(nb, start->id, start->id, face);

                
                faces.push_back(face);
                face.clear();
            } 
        }
        
        //If it already visited al arcs, finishes the iteration
        if(visitedArcs == arcQty){
            i = size;
        } 
    }
    return faces;
}

