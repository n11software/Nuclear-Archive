//
//  main.cpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.hpp"

int main() {
    std::string filename = "/Users/fire/Desktop/Nuclear/Nuclear/main.nuke";
    std::string data = "";
    std::fstream file;
    file.open(filename, std::ios::in);
    if (!file) {
        std::cout << "The file '" + filename + "' was not found!" << std::endl;
        return -1;
    }
    char ch;
    while (1) {
        file >> ch;
        if (file.eof()) break;
        data += ch;
    }
    Lexer lexer = Lexer(data);
    std::vector<std::string> tokens;
    Error error = Error();
    lexer.getTokens(&tokens, &error);
    if (error.getError() != "") std::cout << error.getError() << std::endl;
    else {
        std::cout << "Hello World!" << std::endl;
    }
    file.close();
}
