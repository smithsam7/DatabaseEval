
#include "InputReader.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

InputReader::InputReader(string in_file) {
    in.open(in_file);

};

char InputReader::getChar() {
    in.get(character);

    if(in.eof()){
        return -1;
    }

    if(character == '\n'){
        linNum++;
    }
    return character;
}

int InputReader::getLineNum(){
    return linNum;
}

char InputReader::peek(){
    in.get(character);
    in.putback(character);
    return character;
}

