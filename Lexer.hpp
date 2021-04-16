//
//  Lexer.hpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <iostream>
#include <vector>

std::string DIGITS = "0123456789";
std::string DIGITS_WITH_DOT = "0123456789.";
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

class Error {
    public:
        Error(std::string name, std::string message);
        Error();
        std::string getError();
    private:
        std::string name = "", message;
};

class IllegalCharacterException : public Error {
    public:
        IllegalCharacterException(char c);
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
        Lexer(std::string data);
        void advance();
        void getTokens(std::vector<std::string>* tokens, Error* error);
        std::string getNumber();
    private:
        std::string data;
        char currentChar;
        int pos = -1;
};

#endif /* Lexer_hpp */
