#ifndef Relation_h
#define Relation_h

#include "Tuple.h"
#include "Scheme.h"
#include <stdio.h>
#include <set>
#include <string>
#include <vector>

#define Tuple vector<string>
#define Scheme vector<string>

using namespace std;

class Relation {
public:
    
    Relation(){}
    Relation(string name, Scheme scheme);
    ~Relation(){};
    
    void setName(string name);
    bool addTuple(const Tuple &t);
    void addScheme(string s);
    void setSchemes(Scheme s);
    unsigned int tupleSize();
    
    Scheme getScheme() const { return scheme; }
    set<Tuple> getTuples() const { return tuples; }
    
    string name;
    Scheme scheme;
    set<Tuple> tuples;
    
    bool operator==(const Relation &r) const{
        return this->getScheme() == r.getScheme() && this->getTuples() == r.getTuples();
    }
    bool operator!=(const Relation &r){
        return !operator==(r);
    }
};



#endif 
