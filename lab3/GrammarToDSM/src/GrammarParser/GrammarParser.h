#pragma once

#include <sstream>
#include "../Common/GrammarSide.h"
#include "../Machine/Machine.h"

class GrammarParser
{
public:
    static Machine ParseGrammarToMachine(std::istream& input, GrammarSide grammarSide);

private:

    static void ParseGrammarToMachine(Machine& machine, std::istream& input, bool isLeftSideGrammar);
};