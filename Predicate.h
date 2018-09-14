
#ifndef Predicate_hpp
#define Predicate_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Predicate  {
    
public:
    Predicate();
    void setID(const string &ID);
    void setParameter(const vector<string> &parameter);
    string toString();
    string getID();
    vector<string> getParameters();
    
    string ID;
    vector<string> parameters;
    
    
    
};

#endif
