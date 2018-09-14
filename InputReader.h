
#ifndef InputReader_h
#define InputReader_h

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class InputReader {
    
public:
    InputReader(string in_file);
    ~InputReader(){};
    
    int getLineNum();
    char getChar();
    char peek();
    
    
private:
    ifstream in;
    char character;
    int linNum = 1;
};


#endif
