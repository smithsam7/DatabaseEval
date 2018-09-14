

#include "Rule.h"
#include "Predicate.h"

using namespace std;

Rule::Rule(){}

void Rule::setHeadPred(Predicate &headPred){
    this->headPredicate =  headPred;
}

void Rule::setPredicates(vector<Predicate> &predicates){
    this->predicates  = predicates;
}

string Rule::toString(){
    string str;
    str +=  headPredicate.toString();
    str += " :- ";
    for (int i = 0; i < (int) predicates.size(); i++) {
        str += predicates[i].toString();
        if(i < (int) predicates.size()-1){
            str += ",";
        }
    }
    str += ".";
    return str;
}




