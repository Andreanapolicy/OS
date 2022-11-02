#include "MachineSaver.h"
#include <iostream>
#include <iterator>

namespace
{
    constexpr auto SEPARATOR = ";";
    constexpr auto FINAL_STATE_SYMBOL = "F";

    void SaveAloneStates(std::ostream& output, const std::vector<client::MachineState>& states, bool needToSkipFirstValue = false)
    {
        if (needToSkipFirstValue)
        {
            output << SEPARATOR;
        }

        for (auto index = 0; index < states.size() - 1; index++)
        {
            output << states[index].states;
            output << SEPARATOR;
        }

        output << states[states.size() - 1].states;
    }

    void SaveStateFinalSettings(std::ostream& output, const std::vector<client::MachineState>& states, bool needToSkipFirstValue = false)
    {
        if (needToSkipFirstValue)
        {
            output << SEPARATOR;
        }

        for (auto index = 0; index < states.size() - 1; index++)
        {
            if (states[index].isFinal)
            {
                output << FINAL_STATE_SYMBOL;
            }
            output << SEPARATOR;
        }

        if (states.at(states.size() - 1).isFinal)
        {
            output << FINAL_STATE_SYMBOL;
        }
    }

    void SaveTransitions(std::ostream& output, const client::Machine& machine)
    {
        int inputsCount = machine.inputData.size();
        int statesCount = machine.states.size();

        for (auto indexI = 0; indexI < inputsCount; indexI++)
        {
            output << machine.inputData.at(indexI);

            for (auto indexJ = 0; indexJ < statesCount; indexJ++)
            {
                output << SEPARATOR;
                auto currentState = machine.machineStates.at(indexI).at(indexJ);
                output << currentState;
            }

            output << std::endl;
        }
    }
}

void MachineSaver::Save(std::ostream& output, const client::Machine& machine)
{
    SaveStateFinalSettings(output, machine.states, true);
    SaveAloneStates(output, machine.states, true);
    SaveTransitions(output, machine);
}
