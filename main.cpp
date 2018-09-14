#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Database.h"
#include <vector>

using namespace std;

int main(int argNum, char* argv[]) {
    
    //Scanner scan("/Users/Samuel/Documents/BYU/Winter '18/CS 236/Lab5/Lab5/in50.txt");
    Scanner scan(argv[1]);
    
    //scan.scanTokens();
    //scan.printTokenList();
    
    Parser parser(scan.scanTokens());
    //scan.printTokenList();
    DatalogProgram dlp = parser.parse();
    Database myDb(dlp);
    
    
    return 0;
}


