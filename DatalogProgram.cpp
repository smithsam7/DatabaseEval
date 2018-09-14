
#include "DatalogProgram.h"
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include <iostream>

using namespace std;

DatalogProgram::DatalogProgram(){
    
}

void DatalogProgram::addToScheme(const Predicate &newScheme){
    schemes.push_back(newScheme);
}

void DatalogProgram::addToFact(const Predicate &newFact){
    facts.push_back(newFact);
}

void DatalogProgram::addToQuery(const Predicate &newQuery){
    queries.push_back(newQuery);
}

void DatalogProgram::addToRule(const Rule &newRule){
    rules.push_back(newRule);
}

void DatalogProgram::addToDomain(const set<string> &newDomain){
    domains = newDomain;
    /*for(string s: domains){
        cout <<  "  " << s << endl;
    }*/
}

void DatalogProgram::print() {
    
    cout << "Schemes(" << schemes.size() << "):" << endl;
    for(int i = 0; i  < (int) schemes.size(); i++){
        cout << "  " << schemes[i].toString() << endl;
    }
    
    cout << "Facts(" << facts.size() << "):" << endl;
    for(int i = 0; i  < (int) facts.size(); i++){
        cout << "  " << facts[i].toString() <<  "." << endl;
    }
    
    cout << "Rules(" << rules.size() << "):" << endl;
    for(int i = 0; i  < (int) rules.size(); i++){
        cout << "  " << rules[i].toString() << endl;
    }
    
    cout << "Queries(" << queries.size() << "):" << endl;
    for(int i = 0; i  < (int) queries.size(); i++){
        cout << "  " << queries[i].toString() << "?" << endl;
    }
    
    cout << "Domain("  << domains.size() << "):"  << endl;
    set<string>::iterator iter;
    for(auto iter = begin(domains); iter != end(domains); iter++){
        cout << "  " << *iter << endl;
    }
    
    
     
    
}
