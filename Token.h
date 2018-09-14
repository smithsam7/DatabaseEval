
#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class Token {
  public:
    enum TokenType {COMMA,PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, COMMENT, STRING, UNDEFINED, MYEOF};
    
    Token();
    Token(TokenType token, string value, int lineNum);
    ~Token(){};
    string formatedToken();
    TokenType  getTokenType();
    string getTokenValue();
    
    
private:
    map<TokenType, string>relation = {{Token::COMMA, "COMMA"},{Token::PERIOD, "PERIOD"},{Token::Q_MARK, "Q_MARK"},{Token::LEFT_PAREN, "LEFT_PAREN"},{Token::RIGHT_PAREN, "RIGHT_PAREN"},{Token::COLON, "COLON"},{Token::COLON_DASH, "COLON_DASH"},{Token::MULTIPLY, "MULTIPLY"},{Token::ADD, "ADD"},{Token::SCHEMES, "SCHEMES"},{Token::FACTS, "FACTS"},{Token::RULES, "RULES"},{Token::QUERIES, "QUERIES"},{Token::ID, "ID"},{Token::COMMENT, "COMMENT"},{Token::STRING, "STRING"},{Token::UNDEFINED, "UNDEFINED"},{Token::MYEOF, "EOF"}};
    TokenType token;
    string value;
    int lineNum = 0;
    

};


#endif
