//
//  main.cpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//
//  Goals:
//      - Remove any stdlib and replace with own code
//      - Implement on Hydra
//      - Finish syntax concept
//

#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.hpp"

int main() {
    std::string filename = "main.nuke";
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
    Lexer lexer = Lexer(filename, data);
    std::vector<std::string> tokens;
    Error error = Error();
    lexer.getTokens(&tokens, &error);
    if (error.getError() != "") std::cout << error.getError() << std::endl;
    else {
        for (int i=0; i < tokens.size(); i++) {
            if (i == tokens.size()-1) {
                std::cout << tokens.at(i) << ']' << std::endl;
            } else if (i == 0) {
                std::cout << '[' << tokens.at(i) << ", ";
            } else {
                std::cout << tokens.at(i) << ", ";
            }
        }
    }
    file.close();
}