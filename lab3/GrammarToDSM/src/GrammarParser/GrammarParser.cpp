#include "GrammarParser.h"

Machine GrammarParser::ParseGrammarToMachine(std::istream& input, GrammarSide grammarSide)
{
    Machine machine;
    grammarSide == GrammarSide::RIGHT
        ? ParseRightGrammarSideToMachine(machine, input)
        : ParseLeftGrammarSideToMachine(machine, input);
    
    return machine;
}

Machine GrammarParser::ParseLeftGrammarSideToMachine(Machine& machine, std::istream& input)
{
    return Machine();
}

Machine GrammarParser::ParseRightGrammarSideToMachine(Machine& machine, std::istream& input)
{
    return Machine();
}
