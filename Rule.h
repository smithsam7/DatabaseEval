
#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
#include <string>
#include "Predicate.h"
#include <vector>

using namespace std;

class Rule{
public:
    Rule();
    void setHeadPred(Predicate &headPred);
    void setPredicates(vector<Predicate> &predicates);
    string toString();

    Predicate headPredicate;
    vector<Predicate> predicates;
    
};


#endif
