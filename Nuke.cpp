//
//  Nuke.cpp
//  Nuclear
//
//  Created by Levi Hicks on 4/15/21.
//

#include "Nuke.hpp"
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

Position::Position() {
    this->index = -1;
    this->ln = 0;
    this->col = -1;
    this->filename = "";
    this->data = "";
}

Position::Position(int index, int ln, int col, std::string filename, std::string data) {
    this->index = index;
    this->ln = ln;
    this->col = col;
    this->filename = filename;
    this->data = data;
}

Position Position::advance(char currentChar) {
    this->index++;
    this->col++;
    if (currentChar == '\n') {
        this->ln++;
        this->col = 0;
    }
    return *this;
}

Position Position::copy() {
    return Position(this->index, this->ln, this->col, this->filename, this->data);
}

Error::Error(Position start, Position end, std::string name, std::string message) {
    this->start = start;
    this->end = end;
    this->name = name;
    this->message = message;
}

Error::Error() {
    this->name = "";
    this->message = "";
}

std::string Error::getError() {
    if (this->name != "") return this->name + ": " + this->message + "\nFile " + this->start.filename + ", at " + std::to_string(this->start.ln+1) + ":" + std::to_string(this->start.col+1) + ":" + std::to_string(this->start.index+1);
    return "";
}

IllegalCharacterException::IllegalCharacterException(Position start, Position end, char c) : Error(start, end, "Illegal Character Exception", '\'' + to_string(c) + '\'') {}

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

Lexer::Lexer(std::string filename, std::string data) {
    this->filename = filename;
    this->data = data;
    this->pos = Position(-1, 0, -1, filename, data);
    this->currentChar = '\0';
    this->advance();
}

void Lexer::advance() {
    this->pos.advance(this->currentChar);
    this->currentChar = this->pos.index < this->data.length()-1 ? this->data[this->pos.index] : '\0';
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
            Position start = this->pos.copy();
            *error = IllegalCharacterException(start, this->pos, currentChar);
            this->advance();
            return;
        }
    }
    return;
}

std::string Lexer::getNumber() {
    std::string digits = "0123456789.";
    std::string numStr = "";
    int dots = 0;
    while (this->currentChar != '\0' && digits.find(this->currentChar) != std::string::npos) {
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
