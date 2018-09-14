
#include "Parser.h"
#include "Predicate.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>


using namespace std;


Parser::Parser(vector<Token> tokens){
    this->tokens  = tokens;
}


DatalogProgram Parser::parse(){
    
    try {
        datalogProgram();
        //cout << "Success!"  << endl;
        //datalogProg.print();
    }
    catch(Token tokenfail){
        //cout << "Failure! " << endl;
        //cout << "  " << tokenfail.Token::formatedToken() << endl;
    }
    return datalogProg;
}

void Parser::match(Token::TokenType t){
    if(curTokenType() == t){
        currentToken = getNextToken();
    }
    else {
        error();
    }
}

void Parser::error() {
    throw currentToken;
}

Token Parser::getNextToken() {
    while(currentToken.getTokenType() == Token::COMMENT){
        tokens.erase(tokens.begin());
        currentToken = tokens[0];
    }
    if(!tokens.empty()){
        prevToken = tokens[0];
        tokens.erase(tokens.begin());
        if(tokens.size() > 0){
        currentToken = tokens[0];
        }
    }
    
    return currentToken;
}

Token::TokenType Parser::curTokenType(){
    currentToken = tokens[0];
    return currentToken.getTokenType();
}

void Parser::datalogProgram() {
    
    match(Token::SCHEMES);
    match(Token::COLON);
    scheme();
    schemeList();
    
    match(Token::FACTS);
    match(Token::COLON);
    factList();
    
    match(Token::RULES);
    match(Token::COLON);
    ruleList();
    
    match(Token::QUERIES);
    match(Token::COLON);
    query();
    queryList();
    
    match(Token::MYEOF);
    
}

void Parser::schemeList() {
    if(currentToken.getTokenType() == Token::ID){
        scheme();
        schemeList();
    }
    else {}
}

void Parser::factList() {
    if(currentToken.getTokenType() == Token::ID) {
        fact();
        factList();
    }
    else {}
}

void Parser::ruleList() {
    if(currentToken.getTokenType() ==  Token::ID) {
        rule();
        ruleList();
    }
    else {}
}


void Parser::queryList(){
    if(currentToken.getTokenType() == Token::ID){
        query();
        queryList();
    }
    else {}
}

void Parser::scheme() {
    Predicate p;

    headPredicate(p);
    datalogProg.addToScheme(p);
}

void Parser::fact() {
    Predicate fact;
    vector<string> strings;
    
    if(currentToken.getTokenType() == Token::ID){
        match(Token::ID);
        fact.setID(prevToken.getTokenValue());
        match(Token::LEFT_PAREN);
        match(Token::STRING);
        strings.push_back(prevToken.getTokenValue());
        domains.insert(prevToken.getTokenValue());
        stringList(strings,domains);
        match(Token::RIGHT_PAREN);
        match(Token::PERIOD);
        fact.setParameter(strings);
    }
    datalogProg.addToFact(fact);
    datalogProg.addToDomain(domains);
}

void Parser::rule() {
    Predicate p;
    Predicate head;
    vector<Predicate> rules;
    
    headPredicate(head);
    match(Token::COLON_DASH);
    predicate(p);
    rules.push_back(p);
    predicateList(rules);
    match(Token::PERIOD);
    Rule r;
    r.setHeadPred(head);
    r.setPredicates(rules);
    datalogProg.addToRule(r);
    
}

void Parser::query() {
    Predicate p;
    
    predicate(p);
    match(Token::Q_MARK);
    datalogProg.addToQuery(p);
}

void Parser::headPredicate(Predicate &p){
    string id;
    vector<string> ids;
    
    
    match(Token::ID);
    id = prevToken.getTokenValue();
    match(Token::LEFT_PAREN);
    match(Token::ID);
    ids.push_back(prevToken.getTokenValue());
    idList(ids);
    match(Token::RIGHT_PAREN);
    
    p.setID(id);
    p.setParameter(ids);
}

void Parser::predicate(Predicate &p) {
    string id;
    vector<string> parameters;
    
    if(currentToken.getTokenType() == Token::ID) {
        match(Token::ID);
        id = prevToken.getTokenValue();
        match(Token::LEFT_PAREN);
        string param;
        parameter(param);
        parameters.push_back(param);
        parameterList(parameters);
        match(Token::RIGHT_PAREN);
        p.setID(id);
        p.setParameter(parameters);
    }
 
}

void Parser::predicateList(vector<Predicate> &rules) {
    Predicate p;
    if(currentToken.getTokenType() == Token::COMMA){
        match(Token::COMMA);
        predicate(p);
        rules.push_back(p);
        predicateList(rules);
    }
    else{}
}

void Parser::parameterList(vector<string> &params) {
    if(currentToken.getTokenType() == Token::COMMA){
        match(Token::COMMA);
        string param;
        parameter(param);
        params.push_back(param);
        parameterList(params);
    }
    else {}
}


void Parser::stringList(vector<string> &strings, set<string> &domains) {
    if(currentToken.getTokenType() == Token::COMMA){
        match(Token::COMMA);
        //if(currentToken.getTokenType() == Token::STRING){
            match(Token::STRING);
            strings.push_back(prevToken.getTokenValue());
            domains.insert(prevToken.getTokenValue());
            stringList(strings, domains);
        //}
        //else {}
    }
    else{}
}


void Parser::idList(vector<string> &ids) {
    if(currentToken.getTokenType() == Token::COMMA){
        match(Token::COMMA);
        if(currentToken.getTokenType() == Token::ID){
            match(Token::ID);
            ids.push_back(prevToken.getTokenValue());
            idList(ids);
        }
        else {}
    }
}

void Parser::parameter(string &parameter) {
    
    if(currentToken.getTokenType() == Token::STRING){
        match(Token::STRING);
        parameter = prevToken.getTokenValue();
    }
    else if(currentToken.getTokenType() == Token::ID){
        match(Token::ID);
        parameter  = prevToken.getTokenValue();
    }
    else {
        expression(parameter);
    }
}

void Parser::expression(string &expression) {
        match(Token::LEFT_PAREN);
        expression = "";
        expression += prevToken.getTokenValue();
        string param;
        parameter(param);
        expression += param;
        oPerator();
        expression += prevToken.getTokenValue();
        parameter(param);
        expression += param;
        match(Token::RIGHT_PAREN);
        expression += prevToken.getTokenValue();
}

void Parser::oPerator() {
    if(currentToken.getTokenType() == Token::ADD){
        match(Token::ADD);
    }
    else if(currentToken.getTokenType() == Token::MULTIPLY){
        match(Token::MULTIPLY);
    } else {
        error();
    }
}









