//
// Created by Marcus Jakobsson on 2023-03-02.
//

#ifndef LABB1_2_PARSING_H
#define LABB1_2_PARSING_H


#include <vector>
#include "lexFile.h"

/*
 <regex> ::= <term> { <regex> }
<term> ::= <String> { "*" | "{" <digit> "}" } | "(" <term> "+" <term> ")" | "." | <escaped_char> | <group_output>
<String> ::= <char> { <char> }
<char> ::= "a-z"
<group_output> ::= <regex> "\\O{" <digit> "}"
<escaped_char> ::= "\\" ("I" | "O")
<digit> ::= "0-9"
 */

struct EvalResult {
    EvalResult() {
    }

    EvalResult(bool find, TokenType type, char stringValue) {
        this->type = type;
        this->stringValue = stringValue;
        this->find = find;
    }

    EvalResult(bool find, TokenType type) {
        this->type = type;
        this->find = find;
    }

    EvalResult(int intValue) {
        this->intValue = intValue;
    }

    EvalResult(bool find) {
        this->find = find;
    }

    char stringValue;
    bool find;
    int intValue;
    TokenType type;
};


void moveVectorPointer();

struct ASTNode {
    virtual EvalResult evaluate(const std::string &str, int &index) = 0;

    std::vector<ASTNode *> children;
};







struct Token : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override;

    TokenType value;
};

struct Regex : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override;
};

struct Term : ASTNode {

    EvalResult evaluate(const std::string &str, int &index) override;


     };

struct String : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override;

};

struct Char : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override;

    char value;
};

struct Group_output : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override {

    }
};

struct Escaped_char : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override {

    }
};

struct Digit : ASTNode {
    EvalResult evaluate(const std::string &str, int &index) override {
        return EvalResult(value);
    }

    int value;
};

Regex *MakeTree(std::vector<tokenStruct> v);

Regex *parseRegex();

Term *parseTerm();

String *parseString();

Char *parseChar(int i);

Group_output *parseGroup_output();

Escaped_char *parseEscaped_char();

Digit *parseDigit();

Digit *parseDigit();
























#endif //LABB1_2_PARSING_H
