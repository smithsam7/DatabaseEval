
#ifndef Scanner_h
#define Scanner_h

#include <stdio.h>
#include "Token.h"
#include "InputReader.h"
#include <vector>

using namespace std;

class Scanner {
    
public:
    
    Scanner(string in_file);
    ~Scanner(){};
    void printTokenList();
    vector<Token> scanTokens();
    string scanComments();
    void scanStrings();
    void scanID(char c);
    
private:

    vector<Token> finishedTokens;
    InputReader input;
};

#endif
