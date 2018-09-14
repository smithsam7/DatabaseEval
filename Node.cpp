

#include "Node.h"

using namespace std;

void Node::setVisited(bool visited){
    this->visited = visited;
};

void Node::setNodeID(int iD){
    nodeId = iD;
};

void Node::addAdjNode(int adjNode){
    adjList.insert(adjNode);
};

int Node::getId(){
    return nodeId;
};

bool Node::getVisited(){
    return visited;
};

set<int> Node::getAdjList() const{
    return adjList;
};


