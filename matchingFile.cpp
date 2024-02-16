//
// Created by Marcus Jakobsson on 2023-03-02.
//

#include "matchingFile.h"





bool match(std::string &text, Regex *Root) {

    std::vector<MachinPos> matches;

    for (int textIndex = 0; textIndex < text.size(); ++textIndex) {
        int endIndex = textIndex;
        if (Root->evaluate(text, endIndex).find) {
            matches.push_back({textIndex, endIndex, text.substr(textIndex, endIndex - textIndex), true});
            textIndex = endIndex - 1;
        } else {
            matches.push_back({textIndex, endIndex, text.substr(textIndex, endIndex - textIndex + 1), false});
        }
    }

    int matchCounter = std::count_if(matches.begin(), matches.end(), [](const MachinPos& matchText) {return matchText.match;});


    std::cout<<"Total Matches: "<<matchCounter<<std::endl;

    for (int i = 0; i < matches.size(); ++i) {
        if (matches[i].match){
            std::cout << "\033[31m" <<matches[i].value << "\033[0m";
        } else{
            std::cout <<matches[i].value;
        }
    }

    return matchCounter;




}
