//
// Created by Marcus Jakobsson on 2023-03-02.
//

#ifndef LABB1_2_LEXFILE_H
#define LABB1_2_LEXFILE_H

#include <string>
enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    LITERAL,
    LEFT_MOOSE,
    SPACE,
    RIGHT_MOOSE,
    MULIPLY,
    ADD,
    DOT,
    BACKSLASH,
    END

};
struct tokenStruct{
    TokenType tokentype;
    std::string value;
    tokenStruct(const std::string& value, TokenType tokentype) : value(value), tokentype(tokentype) {}
    tokenStruct(){}
};
std::vector<tokenStruct> generateLex(const std::string& inputString);
TokenType lex(char expr);



#endif //LABB1_2_LEXFILE_H
