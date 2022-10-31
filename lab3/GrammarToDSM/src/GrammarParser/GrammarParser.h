#pragma once

#include <sstream>

class GrammarParser
{
public:
    static Machine GetLeftSideGrammar(std::istream& input);

    static Machine GetRightSideGrammar(std::istream& input);
};