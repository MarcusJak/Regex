
#include <vector>
#include "matchingFile.h"

/*

<regex>        ::= <term> [<escaped_char>] [<regex>]

<term>         ::= <string> [”*” | "{" <digit> "}" ]
                  | "(" <term> "+" <term> ")"
                  | "." ["{" <digit> "}" | ”*”]

<string>       ::= <char> { <char> }
<char>         ::= a-z | A-Z | space
<escaped_char> ::= "\\" ( "I" | "O" "{" <digit> "}" )
<digit>        ::= [0-9]+


 */


int main(int argc, char* argv[]) {
    std::string expr = argv[1];
    std::string text = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    auto dataLex = generateLex(expr);

    auto p_Regex= MakeTree(dataLex);

    if (p_Regex== nullptr){
       return EXIT_FAILURE;
    }
    
    auto ans=match(text, p_Regex);

    if (ans)
    {
    return EXIT_SUCCESS;
    } else{
      return EXIT_FAILURE;
    }

}


