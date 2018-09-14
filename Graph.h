
#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <map>
#include "Node.h"
#include <stack>
#include <set>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(){};
    ~Graph(){};
    
    void dfs(int nodeId);
    void dfsSCC(int nodeId);
    void dfsForest();
    void insertNode(int nodeId, Node &node);
    void addAdjNode(int nodeId, int adjNodeId);
    stack<int> getPON();
    
    map<int, Node> getGraph();
    
    map<int, Node> graphNodes;
    set<int> SCC;
    vector<set<int>> SCCs;
    stack<int> postOrderNum;
    
    
    
};



#endif /* Graph_h */
