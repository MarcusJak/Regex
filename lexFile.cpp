//
// Created by Marcus Jakobsson on 2023-03-02.
//

#include "lexFile.h"
#include <iostream>
#include <vector>
#include <map>


std::map<char, TokenType> char2Token = {
        {'*', MULIPLY},
        {'+', ADD},
        {'.', DOT},
        {' ', SPACE},
        {'(', LEFT_PAREN},
        {')', RIGHT_PAREN},
        {'{', LEFT_MOOSE},
        {'}', RIGHT_MOOSE},
        {'\\', BACKSLASH}
};

TokenType lex(char expr) {
    auto it = char2Token.find(expr);
    if (it != char2Token.end()) {
        return it->second;
    } else {
        return LITERAL;
    }
}



std::vector<tokenStruct> generateLex(const std::string& inputString) {
    std::vector<tokenStruct> tokens;

    std::string tempString;
    tokenStruct temp;

    for (char c : inputString) {
        TokenType tokenType = lex(c);
        if (tokenType == LITERAL || tokenType == SPACE) {
            tempString += c;
        } else {
            if (!tempString.empty()) {
                tokens.push_back({tempString, LITERAL});
                tempString.clear();
            }
            tokens.push_back({"", tokenType});
        }
    }

    if (!tempString.empty()) {
        tokens.push_back({tempString, LITERAL});
    }

    tokens.push_back({"", END});

    return tokens;
}