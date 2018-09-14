
#ifndef Parser_h
#define Parser_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"

using namespace std;

class Parser {
    
public:
    
    Parser(vector<Token> tokens);
    ~Parser(){};
    
    DatalogProgram parse();
    void match(Token::TokenType t);
    void error();
    
    void datalogProgram();
    
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    
    void scheme();
    void fact();
    void rule();
    void query();
    
    void headPredicate(Predicate &p);
    void predicate(Predicate &p);
    
    void predicateList(vector<Predicate> &rules);
    void parameterList(vector<string> &params);
    void stringList(vector<string> &strings, set<string> &domains);
    void idList(vector<string> &ids);
    
    void parameter(string &parameter);
    void expression(string &expression);
    void oPerator();
    
    Token getNextToken();
    Token::TokenType curTokenType();
    
private:
    vector<Token> tokens;
    Token currentToken;
    DatalogProgram datalogProg;
    Token  prevToken;
    set<string> domains;

};




#endif
