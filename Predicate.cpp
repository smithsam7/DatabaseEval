
#include "Predicate.h"
#include <iostream>

using namespace std;


Predicate::Predicate(){}

void Predicate::setID(const string &ID){
    this->ID =  ID;
}

void Predicate::setParameter(const vector<string> &parameter) {
    this->parameters = parameter;
}

string Predicate::toString(){
    string str;
    str += ID;
    str += "(";
    for(int i = 0; i < (int) parameters.size(); i++){
        str += parameters[i];
        if(i < (int) parameters.size()-1){
            str += ",";
        }
    }
    str += ")";
    return str;
}

string Predicate::getID(){
    return ID;
}

vector<string> Predicate::getParameters(){
    return parameters;
}
