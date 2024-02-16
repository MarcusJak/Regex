//
// Created by Marcus Jakobsson on 2023-03-02.
//
#include <iostream>
#include "parsing.h"

#ifndef LABB1_2_MATCHINGFILE_H
#define LABB1_2_MATCHINGFILE_H

bool match(std::string &text, Regex *Root);
struct MachinPos{
    MachinPos(int startPos, int endPos, std::string value, bool match){
        this->startPos=startPos;
        this->endPos=endPos;
        this->value=value;
        this->match=match;

    }
    bool match;
    int startPos;
    int endPos;
    std::string value;
};




#endif //LABB1_2_MATCHINGFILE_H
