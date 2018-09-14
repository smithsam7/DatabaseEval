#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <set>

using namespace std;

class Node {
public:
    Node(){};
    ~Node(){};
    
    void setVisited(bool visited);
    void setNodeID(int iD);
    void addAdjNode(int adjNode);
    
    int getId();
    bool getVisited();
    set<int> getAdjList() const;

    
    set<int> adjList;
    int nodeId = -1;
    bool visited = false;
    bool selfDependent = false;

   
    
    
    
};



#endif /* Node_h */
