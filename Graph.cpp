
#include "Graph.h"
#include <stack>
#include <iostream>

using namespace std;






void Graph::insertNode(int nodeId, Node &node){
    graphNodes[nodeId] = node;
};

void Graph::addAdjNode(int nodeId, int adjNodeId){
    graphNodes[nodeId].addAdjNode(adjNodeId);
};

map<int, Node> Graph::getGraph(){
    return graphNodes;
};

stack<int> Graph::getPON(){
    return postOrderNum;
}


void Graph::dfs(int nodeId){
    //cout << "Vistied:" << graphNodes[nodeId].getVisited() << endl;
    //cout << "Id: " << graphNodes[nodeId].getId() << endl;
    
    if(graphNodes[nodeId].visited != true){
        //bool visited = true;
        graphNodes[nodeId].visited = true;
        for(set<int>::iterator iter = graphNodes[nodeId].adjList.begin(); iter != graphNodes[nodeId].adjList.end(); ++iter){
            int adjNode = *iter;
            dfs(adjNode);
        }
        //cout << graphNodes[nodeId].nodeId << endl;
        postOrderNum.push(graphNodes[nodeId].nodeId);
    }
    return;
}

void Graph::dfsForest(){
    for(map<int, Node>::iterator iter = graphNodes.begin(); iter != graphNodes.end(); ++iter){
        if(iter->second.visited != true){
            dfs(iter->first);
        }
    }
}

void Graph::dfsSCC(int nodeId){
    if(graphNodes[nodeId].visited != true){
        graphNodes[nodeId].visited = true;
        for(set<int>::iterator iter = graphNodes[nodeId].adjList.begin(); iter != graphNodes[nodeId].adjList.end(); ++iter){
            int adjNode = *iter;
            dfsSCC(adjNode);
        }
        SCC.insert(nodeId);
    }
}


