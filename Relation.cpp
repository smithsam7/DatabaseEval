

#include "Relation.h"

using namespace std;

Relation::Relation(string name, Scheme schemes) {
    setName(name);
    setSchemes(schemes);
}

bool Relation::addTuple(const Tuple &t){
    return tuples.insert(t).second;
}

void Relation::addScheme(string s){
    scheme.push_back(s);
}

void Relation:: setSchemes(Scheme s){
    this->scheme = s;
    
}

void Relation::setName(string name){
    this->name = name;
}

unsigned int Relation::tupleSize(){
    return tuples.size();
}


