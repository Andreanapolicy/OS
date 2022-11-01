#include "GrammarParser.h"
#include "../Common/Utils.h"

namespace
{
    struct Transition
    {
        std::string state;
        std::string inputData;
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

    void AddNewStateToMachine(Machine& machine, const std::string& state)
    {
        auto it = std::find(machine.states.begin(), machine.states.end(), state);

        if (it == machine.states.end())
        {
            machine.states.emplace_back(state);
            for (auto& transitionStates: machine.machineStates)
            {
                if (transitionStates.size() != machine.states.size())
                {
                    transitionStates.emplace_back(MachineState{std::set<std::string>(), false});
                }
            }
        }
    }

    void AddNewInputDataToMachine(Machine& machine, const std::string& inputData)
    {
        auto it = std::find(machine.inputData.begin(), machine.inputData.end(), inputData);

        if (it == machine.inputData.end())
        {
            machine.inputData.emplace_back(inputData);
            machine.machineStates.emplace_back(std::vector<MachineState>(machine.states.size(), MachineState{std::set<std::string>(), false}));
        }
    }

    void FillMachineByState(Machine& machine, const std::string& state,  const std::vector<Transition>& transitions)
    {
        AddNewStateToMachine(machine, state);
        size_t inputDataIndex = 0;
        size_t stateIndex = std::distance(machine.states.begin(), std::find(machine.states.begin(), machine.states.end(), state));

        for (const auto& transition : transitions)
        {
            std::string inputData = transition.inputData;
            std::string newState = transition.state.empty() ? DEFAULT_FINAL_STATE : transition.state;

            AddNewInputDataToMachine(machine, inputData);
            AddNewStateToMachine(machine, newState);
            inputDataIndex = std::distance(machine.inputData.begin(), std::find(machine.inputData.begin(), machine.inputData.end(), inputData));

            try
            {
                std::cout << newState << std::endl;
                machine.machineStates.at(inputDataIndex).at(stateIndex).states.emplace(newState);
                machine.machineStates.at(inputDataIndex).at(stateIndex).isFinal = newState == DEFAULT_FINAL_STATE;
            }
            catch (...)
            {
                machine.machineStates.at(inputDataIndex).emplace_back(MachineState{std::set<std::string>{newState}, newState == DEFAULT_FINAL_STATE});
            }
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

void GrammarParser::ParseLeftGrammarSideToMachine(Machine& machine, std::istream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::string state;
        std::string trash;
        iss >> state;

        iss >> trash;

        std::vector<Transition> transitions;
        FillTransitions(transitions, iss, true);
        FillMachineByState(machine, state, transitions);
    }

}

void GrammarParser::ParseRightGrammarSideToMachine(Machine& machine, std::istream& input)
{
}
