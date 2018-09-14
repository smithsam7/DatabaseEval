
#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Parser.h"
#include "Relation.h"
#include "Graph.h"
#include "RelationalAl.h"

using namespace std;

class Database {
public:
    Database(DatalogProgram dlp){
        mySchemes = dlp.schemes;
        myFacts = dlp.facts;
        myQueries = dlp.queries;
        myRules = dlp.rules;
        createRelation();
        buildGraph();
        printDepGraph();
        createSCCs();
        evalRules();
        evalQueries();
    };
    ~Database(){};
    
    vector<Predicate> mySchemes;
    vector<Predicate> myFacts;
    vector<Predicate> myQueries;
    vector<Rule> myRules;
    
    map<string, Relation> originalR;
    Graph forwardGraph;
    Graph reverseGraph;
    
    int passesInRules = 0;
    bool noAddedTuples;
    
    void createSCCs();
    void printDepGraph();
    void printMultRules(set<int> SCC);
    void buildGraph();
    void evalRules();
    void evalSet(set<int> SCC);
    void evalOneRule(set<int> SCC);
    void createRelation();
    void evalQueries();
    void printSelections(const Relation &r, Predicate querry);
    void printRules(Rule &r);
    int numTuples(map<string, Relation> &mapR);
};



#endif
