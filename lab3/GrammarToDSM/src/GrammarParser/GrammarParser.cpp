#include "GrammarParser.h"
#include "../Common/Utils.h"

namespace
{
    struct Transition
    {
        std::string state;
        std::string inputData;
    };

    struct StatesGrammar
    {
        std::string originState;
        std::vector<Transition> transitions;
    };

    void FillTransitions(std::vector<Transition>& transitions, std::istream& input, bool isLeftSideGrammar)
    {
        std::string transition;

        while (std::getline(input, transition, '|'))
        {
            std::string state;
            std::string inputData;
            auto index = 0;

            transition = trim(transition);
            if (transition.size() == 1)
            {
                transitions.emplace_back(Transition{"", transition});

                continue;
            }

            if (isLeftSideGrammar)
            {
                state = transition.substr(0, 1);
                inputData = transition.substr(1, transition.length() - 1);
            }
            else
            {
                state = transition.substr(1, transition.length() - 1);
                inputData = transition.substr(0, 1);
            }

            transitions.emplace_back(Transition{state, inputData});
        }
    }
}

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
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::string state;
        std::string trash;
        iss >> state;
        machine.inputData.emplace_back(state);

        iss >> trash;

        std::vector<Transition> transitions;
        FillTransitions(transitions, iss, true);

        //auto stateGrammar = GetStateGrammar(input);
    }

    return Machine();
}

Machine GrammarParser::ParseRightGrammarSideToMachine(Machine& machine, std::istream& input)
{
    return Machine();
}
