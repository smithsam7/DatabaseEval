
#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <stdio.h>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
using namespace std;

class DatalogProgram  {
    
public:
    DatalogProgram();
    void addToScheme(const Predicate &newScheme);
    void addToFact(const Predicate &newFact);
    void addToQuery(const Predicate &newQuery);
    void addToRule(const Rule &newRule);
    void addToDomain(const set<string> &newDomain);
    void print();

    
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> domains;
};




#endif 
