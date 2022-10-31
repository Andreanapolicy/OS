#pragma once

#include <sstream>
#include "../Common/GrammarSide.h"

class GrammarParser
{
public:
    static Machine ParseGrammarToMachine(std::istream& input, GrammarSide grammarSide);
};