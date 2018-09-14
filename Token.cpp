
#include "Token.h"
#include <map>
#include <string>
using namespace std;

Token::Token () : Token(Token::UNDEFINED, "", -1){
}

Token::Token(TokenType token, string value, int lineNum){
    this->token = token;
    this->value = value;
    this->lineNum = lineNum;
}

string Token::formatedToken(){
    return "(" + relation[token] + ",\"" + value + "\"," + to_string(lineNum) + ")";
}

Token::TokenType Token::getTokenType() {
    return token;
}

string Token::getTokenValue(){
    return value;
}
