#pragma once

#include <map>
#include "../Common/Automat.h"
#include "../Common/LetterRandomizer.h"

class MachineConverter
{
public:
    Machine static GetMooreMachineFromMealy(const Machine& machine)
    {
        Machine newMachine;
        auto newStates = CreateMapStates(machine);
        return {};
    }

    Machine static GetMealyMachineFromMoore(const Machine& machine)
    {
        return {};
    }

private:
    std::map<std::string, MachineState> static CreateMapStates(const Machine& machine)
    {
        std::string newStateName = {GetRandomLetter(machine.states.at(0).at(0))};
        std::map<std::string, MachineState> transitionMap;

        for (auto const& transitionLine: machine.machineStates)
        {
            for (auto const& state: transitionLine)
            {
                if (!isValueExist(transitionMap, state))
                {
                    transitionMap.insert(std::make_pair(newStateName + (char)transitionMap.size(), state));
                }
            }
        }

        return transitionMap;
    }

    bool static isValueExist(const std::map<std::string, MachineState>& machineMap, const MachineState& state)
    {
        for (const auto& [key, value]: machineMap)
        {
            if (value.state == state.state)
            {
                return true;
            }
        }
        return false;
    }
};