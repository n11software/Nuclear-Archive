//
//  Lexer.cpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//

#include "Lexer.hpp"
#include <string>

std::string to_string(char c) {
    std::string s = "";
    s += c;
    return s;
}

std::string to_char(std::string s) {
    char p[s.length()];
    int i;
    for (i = 0; i < sizeof(p); i++) {
        p[i] = s[i];
    }
    return p;
}

Error::Error(std::string name, std::string message) {
    this->name = name;
    this->message = message;
}

Error::Error() {}

std::string Error::getError() {
    return this->name + ": " + this->message;
}

IllegalCharacterException::IllegalCharacterException(char c) : Error("Illegal Character Exception", to_string(c)) {}

Token::Token(std::string type) {
    this->type = type;
}

Token::Token(std::string type, std::string value) {
    this->type = type;
    this->value = value;
}

std::string Token::getString() {
    if (value != "") return type + ':' + value;
    return type;
}

Lexer::Lexer(std::string data) {
    this->data = data;
    this->pos = -1;
    this->currentChar = '\0';
    advance();
}

void Lexer::advance() {
    this->pos++;
    this->currentChar = this->pos < this->data.length() ? this->data[this->pos] : '\0';
}

void Lexer::getTokens(std::vector<std::string>* tokens, Error* error) {
    std::string digits = "0123456789";
    while (this->currentChar != '\0') {
        if (this->currentChar == ' ' || this->currentChar == '\n' || this->currentChar == '\t') {
            this->advance();
        } else if (digits.find(this->currentChar) != std::string::npos) {
            tokens->push_back(this->getNumber());
        } else if (this->currentChar == '+') {
            tokens->push_back(Token(TokenPlus).getString());
            this->advance();
        } else if (this->currentChar == '-') {
            tokens->push_back(Token(TokenMinus).getString());
            this->advance();
        } else if (this->currentChar == '*') {
            tokens->push_back(Token(TokenMultiply).getString());
            this->advance();
        } else if (this->currentChar == '/') {
            tokens->push_back(Token(TokenDivide).getString());
            this->advance();
        } else if (this->currentChar == '(') {
            tokens->push_back(Token(TokenLeftParenthesis).getString());
            this->advance();
        } else if (this->currentChar == ')') {
            tokens->push_back(Token(TokenRightParenthesis).getString());
            this->advance();
        } else {
            this->advance();
            *error = IllegalCharacterException(currentChar);
            return;
        }
    }
    return;
}

std::string Lexer::getNumber() {
    std::string digitsDot = "0123456789.";
    std::string numStr = "";
    int dots = 0;
    while (this->currentChar != '\0' && digitsDot.find(this->currentChar) != std::string::npos) {
        if (this->currentChar == '.') {
            if (dots == 1) break;
            dots++;
            numStr += '.';
        } else numStr += currentChar;
        this->advance();
    }
    if (dots == 0) return Token(TokenInteger, std::to_string(std::stoi(numStr))).getString();
    return Token(TokenFPD, std::to_string(std::stof(numStr))).getString();
}
