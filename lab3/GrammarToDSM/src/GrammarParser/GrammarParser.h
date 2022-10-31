#pragma once

#include <sstream>
#include "../Common/GrammarSide.h"
#include "../Machine/Machine.h"

class GrammarParser
{
public:
    static Machine ParseGrammarToMachine(std::istream& input, GrammarSide grammarSide);

private:
    static Machine ParseLeftGrammarSideToMachine(Machine& machine, std::istream& input);

    static Machine ParseRightGrammarSideToMachine(Machine& machine, std::istream& input);
};