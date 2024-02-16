//
// Created by Marcus Jakobsson on 2023-03-02.
//

#include <iostream>
#include "parsing.h"
#include <cctype>

std::vector<tokenStruct>::iterator p_this;
std::vector<tokenStruct>::iterator p_next;

void moveVectorPointer(){
    p_this++;
    p_next++;
}



Digit *parseDigit() {
    auto p_Digit = new Digit;

    if (p_this->value.find_first_not_of("0123456789") == std::string::npos) {
        auto num = std::stoi(p_this->value);
        p_Digit->value=num;
    }
    else {
        return nullptr;
    }

    return p_Digit;
}

Char* parseChae(){
    auto p_Char =new Char;




    return p_Char;
}



Escaped_char *parseEscaped_char() {
    auto p_Escaped_char = new Escaped_char;


    return p_Escaped_char;
}

Group_output* parseGroup_output(){

    auto p_Group_output = new Group_output;

    return p_Group_output;
}




Char* parseChar(int i){

    if (isalpha(p_this->value[i])||p_this->value[i]==32)
    {
        auto p_Char = new Char;
        p_Char->value=p_this->value[i];
        return p_Char;
    }
    else{return nullptr;}

}


//<String> ::= <char> { <char> }
String* parseString(){
    auto p_String = new String;
    if (p_this->tokentype!=LITERAL){
        return nullptr;
    }

    auto t=p_this->value.size();
    for (int i = 0; i < t; ++i) {

        auto p_firstChar = parseChar(i);
        if(p_firstChar!= nullptr){
            p_String->children.push_back(p_firstChar);
        } else{return nullptr;}
    }
    moveVectorPointer();
    return  p_String;

}

//"{" <digit> "}"
Term* upCounting(){
    auto p_ReturnTerm =new Term;
    auto p_token = new Token;
    p_token = new Token;
    p_token->value=p_this->tokentype;
    p_ReturnTerm->children.push_back(p_token);
    moveVectorPointer();

    auto p_digit=parseDigit();

    if (p_digit== nullptr){
        auto p_digit_default= new Digit;
        p_digit_default->value=0;
        p_ReturnTerm->children.push_back(p_digit_default);
    } else{
        p_ReturnTerm->children.push_back(p_digit);
        moveVectorPointer();
    }
    p_token = new Token;
    p_token->value=p_this->tokentype;
    p_ReturnTerm->children.push_back(p_token);
    moveVectorPointer();

    return p_ReturnTerm;

}

/*
<term> ::= <string> [ ( ”*”  |   "."  | "{" <digit> "}"]
| "(" <term> "+" <term> ")"
|  "."["{" <digit> "}"]
*/
Term* parseTerm(){

    auto p_Term = new Term;

    auto p_First_factor= parseString();
    //<term> ::= <string> [ ( ”*”  |   "."  | "{" <digit> "}"]
    if(p_First_factor!= nullptr)
    {
        p_Term->children.push_back(p_First_factor);
        //moveVectorPointer();

        // ”*”  |   "."
        if ( p_this->tokentype ==MULIPLY ) {
            auto p_token = new Token;
            p_token->value=p_this->tokentype;
            p_Term->children.push_back(p_token);
            moveVectorPointer();
        }
        // "{" <digit> "}
        else if (p_this->tokentype==LEFT_MOOSE){
                auto reponseCounter=upCounting();
                for (int i = 0; i < reponseCounter->children.size(); ++i) {

                    p_Term->children.push_back(reponseCounter->children[i]);
                }

            }
        }

    //"(" <term> "+" <term> ")"
    else if (p_this->tokentype ==LEFT_PAREN ) {
        auto p_token = new Token;
        p_token->value = p_this->tokentype;
        p_Term->children.push_back(p_token);
        moveVectorPointer();

        //first
        auto p_first_term= parseTerm();
        p_Term->children.push_back(p_first_term);
        //moveVectorPointer();

        //add
        p_token = new Token;
        p_token->value = p_this->tokentype;
        p_Term->children.push_back(p_token);
        moveVectorPointer();

        //secund
        auto p_Secund_term= parseTerm();
        p_Term->children.push_back(p_Secund_term);
        //moveVectorPointer();

        p_token = new Token;
        p_token->value = p_this->tokentype;
        p_Term->children.push_back(p_token);
        moveVectorPointer();
    }

    //"."
    else if (p_this->tokentype == DOT)
    {
        auto p_token = new Token;
        p_token->value = p_this->tokentype;
        p_Term->children.push_back(p_token);
        moveVectorPointer();
         if (p_this->tokentype==LEFT_MOOSE){
             auto reponseCounter=upCounting();
             for (int i = 0; i < reponseCounter->children.size(); ++i) {

                 p_Term->children.push_back(reponseCounter->children[i]);
             }

        }

         else if(p_this->tokentype==MULIPLY){
             auto p_token = new Token;
             p_token->value=p_this->tokentype;
             p_Term->children.push_back(p_token);
             moveVectorPointer();
         }

    }

    else{
        return nullptr;
    }

    return  p_Term;
}

//<regex> ::= <term> [<escaped_char>] [ <regex> ]
Regex* parseRegex(){
    auto p_Regex = new Regex;

    auto p_First_Term= parseTerm();

    if(p_First_Term == nullptr){
        return nullptr;
    } else{
        p_Regex->children.push_back(p_First_Term);
    }
    auto p_nextRegex=parseRegex();
            if(p_nextRegex!= nullptr){
                p_Regex->children.push_back(p_nextRegex);
            }
    return p_Regex;
}


//Make tree root mm...
Regex * MakeTree(std::vector<tokenStruct> v)
{
    p_this=v.begin();
    p_next=v.begin()+1;

    auto p_Root= parseRegex();

    if (p_this->tokentype!=END){
        std::cout<<"Expr dont follow roles!"<<std::endl<<"error:"<<std::distance(v.begin(), p_this)+1 <<":e token"<<std::endl<<std::endl;
    }
    return p_Root;
}





//Regex (root)
EvalResult Regex::evaluate(const std::string &str, int &index) {
    int i = index;
    for (ASTNode *child: children) {
        if (!child->evaluate(str, i).find) {
            return {false};
        }
    }
    index = i;
    return {true};
}


//term
EvalResult Term::evaluate(const std::string &str, int &index) {


    for (int i = 0; i < children.size(); ++i) {

        auto kid = children[i]->evaluate(str, index);

// "(" <term> "+" <term> ")"
        if (kid.type == LEFT_PAREN) {
            i++;

            if (!children[i]->evaluate(str, index).find && !children[i+2]->evaluate(str, index).find) {
                return {false};
            }
            else {
                i += 3;
            }
        }



// "." ["{" <digit> "}"]
        else if (kid.type == DOT) {
            i++;
            if (i < children.size()) {
                kid = children[i]->evaluate(str, index);
                if (kid.type == LEFT_MOOSE) {
                    i++;
                    auto temp = children[i]->evaluate(str, index);
                    index += temp.intValue - 1;
                }
                else if (kid.type==MULIPLY){
                        while (index<str.size()) {
                                index++;
                            }
                        }

                }
            return {true};

        }


        else if (kid.type == LEFT_MOOSE) {
            i++;
            kid = children[i]->evaluate(str, index);
            for (int j = 0; j < kid.intValue; ++j) {

                if (!children[i - 2]->evaluate(str, index).find) {
                    return {false};
                }
            }

            i++;
        }



//<string> [”*” | "{" <digit> "}" ]
        else if (kid.type == LITERAL && kid.find) {
            i++;
            if (i < children.size()) {
                char lastChar = kid.stringValue;
                kid = children[i]->evaluate(str, index);

                if (kid.type == MULIPLY) {

                    while (true) {
                        if (str[index] == lastChar) {
                            index++;
                        } else {
                            break;
                        }
                    }
                }

                else if (kid.type == LEFT_MOOSE) {
                    i++;
                    kid = children[i]->evaluate(str, index);
                    for (int j = 0; j < kid.intValue - 1; ++j) {

                        if (str[index] == lastChar) {
                            index++;
                        } else {
                            return {false};
                        }
                    }
                }


                return {true};
            }
        }
        else{
            return {false};
        }


    }


    return {true};
}




//string
EvalResult String::evaluate(const std::string &str, int &index) {
    int i = index;
    EvalResult lastChar;
    for (ASTNode *child: children) {
        lastChar = child->evaluate(str, i);
        if (!lastChar.find) {
            return {false, LITERAL, lastChar.stringValue};
        }

    }
    index = i;
    return {true, LITERAL, lastChar.stringValue};
}

//char
EvalResult Char::evaluate(const std::string &str, int &index) {
    if (index >= str.size() || str[index] != value) {
        return {false, LITERAL};
    }
    index++;
    return {true, LITERAL, value};
}

//token
EvalResult Token::evaluate(const std::string &str, int &index) {

    if (value==DOT){
        index++;
        return {true,value};
    }

    return {true, value};
}
