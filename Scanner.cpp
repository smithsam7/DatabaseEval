

#include "Scanner.h"
#include <string>
#include <sstream>


Scanner::Scanner(string in_file):input(in_file) {
}

vector<Token> Scanner::scanTokens() {
    char currentChar = 0;
    while (currentChar != -1) {
        currentChar = input.getChar();
        
        switch (currentChar) {
            case ',':
                finishedTokens.push_back(Token(Token::COMMA, ",", input.getLineNum()));
                break;
            case '.':
                finishedTokens.push_back(Token(Token::PERIOD, ".", input.getLineNum()));
                break;
            case '?':
                finishedTokens.push_back(Token(Token::Q_MARK, "?", input.getLineNum()));
                break;
            case '(':
                finishedTokens.push_back(Token(Token::LEFT_PAREN, "(", input.getLineNum()));
                break;
            case ')':
                finishedTokens.push_back(Token(Token::RIGHT_PAREN, ")", input.getLineNum()));
                break;
            case ':':
                if(input.peek() == '-'){
                    input.getChar();
                    finishedTokens.push_back(Token(Token::COLON_DASH, ":-", input.getLineNum()));
                }
                else {
                finishedTokens.push_back(Token(Token::COLON, ":", input.getLineNum()));
                }
                break;
            case '*':
                finishedTokens.push_back(Token(Token::MULTIPLY, "*", input.getLineNum()));
                break;
            case '+':
                finishedTokens.push_back(Token(Token::ADD, "+", input.getLineNum()));
                break;
            case '#':
                //finishedTokens.push_back(Token(Token::COMMENT, scanComments(), input.getLineNum()));
                scanComments();
                break;
            case '\'':
                scanStrings();
                break;
            default:
                if(isalpha(currentChar)){
                    scanID(currentChar);
                }
                else if(!isspace(currentChar) && currentChar != -1){
                    string s;
                    s += currentChar;
                    finishedTokens.push_back(Token(Token::UNDEFINED, s, input.getLineNum()));
                }
                break;
        }
    } finishedTokens.push_back(Token(Token::MYEOF, "", input.getLineNum()));
    return finishedTokens;
};

void Scanner::printTokenList(){
    for(unsigned int i = 0; i < finishedTokens.size(); i++){
        cout << finishedTokens[i].formatedToken() << endl;
    }
    cout << "Total Tokens = " << finishedTokens.size() << endl;
}

string Scanner::scanComments(){
    string cha;
    string s = "#";
    if(input.peek() == '|'){
        while (s.length() <= 2 || (s[s.length()-1] != '|' && input.peek() != '#')) {
            cha = input.getChar();
            s += cha;
        }
        s += input.getChar();
    }
    else {
        while (input.peek() != '\n') {
            cha = input.getChar();
            s += cha;
        }
    }
    return s;
}

void Scanner::scanStrings(){
    int line = input.getLineNum();
    char cha = input.getChar();
    string s = "'";
    while (cha != -1) {
        if(cha == '\''){
            if(input.peek() == '\''){
                s += cha;
                s += input.getChar();
                cha = input.getChar();
            }
            else{
                break;
            }
        }
        else{
            s += cha;
            cha = input.getChar();
        }
    }
    if(cha == '\''){
        finishedTokens.push_back(Token(Token::STRING, s + cha, line));
    }
    else {
        finishedTokens.push_back(Token(Token::UNDEFINED, s, line));
    }
}

void Scanner::scanID(char c){
    string s;
    s += c;
    while (isalnum(input.peek())){
        s += input.getChar();
    }
    if(s == "Schemes"){
        finishedTokens.push_back(Token(Token::SCHEMES, s, input.getLineNum()));
    }
    else if(s == "Facts"){
        finishedTokens.push_back(Token(Token::FACTS, s, input.getLineNum()));
    }
    else if (s == "Rules"){
        finishedTokens.push_back(Token(Token::RULES, s, input.getLineNum()));
    }
    else if(s == "Queries"){
        finishedTokens.push_back(Token(Token::QUERIES, s, input.getLineNum()));
    }
    else {
        finishedTokens.push_back(Token(Token::ID, s, input.getLineNum()));
    }
    
}







