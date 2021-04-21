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
#include "Nuke.hpp"

int main() {
    std::string filename = "main.nuke";
    std::string data = "";
    char ch;
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file) {
        std::cout << "File lost or not found!" << std::endl;
        std::cout << "Failed to compile; error whilst getting file data!" << std::endl;
        return -1;
    }
    while (!file.eof()) {
        file >> std::noskipws >> ch;
        data += ch;
    }
    file.close();
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