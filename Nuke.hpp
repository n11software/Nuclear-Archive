//
//  Nuke.hpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//

#ifndef Nuke_hpp
#define Nuke_hpp

#include <iostream>
#include <vector>

#define TokenInteger "INT"
#define TokenFPD "FPD"
#define TokenPlus "PLUS"
#define TokenMinus "MINUS"
#define TokenMultiply "MULTIPLY"
#define TokenDivide "DIVIDE"
#define TokenLeftParenthesis "LP"
#define TokenRightParenthesis "RP"

std::string to_string(char c);
std::string to_char(std::string str);

class Position {
    public:
        Position();
        Position(int index, int ln, int col, std::string filename, std::string data);
        Position advance(char currentChar);
        Position copy();
        int index, ln, col;
        std::string filename, data;
};

class Error {
    public:
        Error(Position start, Position end, std::string name, std::string message);
        Error();
        std::string getError();
    private:
        std::string name = "", message = "";
        Position start, end;
};

class IllegalCharacterException : public Error {
    public:
        IllegalCharacterException(Position start, Position end, char c);
};

class Token {
    public:
        Token(std::string type);
        Token(std::string type, std::string value);
        std::string getString();
    private:
        std::string type;
        std::string value = "";
};

class Lexer {
    public:
        Lexer(std::string filename, std::string data);
        void advance();
        void getTokens(std::vector<std::string>* tokens, Error* error);
        std::string getNumber();
    private:
        std::string filename, data;
        char currentChar;
        Position pos;
};

#endif /* Nuke_hpp */