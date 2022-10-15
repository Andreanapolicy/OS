#include "MachineMinimizator.h"

#include "unordered_map"
#include "../Common/Lettering.h"

namespace
{
    struct MachineWithEquivalentStates : public Machine
    {
        std::unordered_map<std::string, std::string> equivalentStates;
    };

    std::unordered_map<std::string, std::string> CreateNewEquivalentStates(const std::unordered_map<std::string, std::string>& transitionsForEquivalentStates)
    {
        auto newEquivalentStates = transitionsForEquivalentStates;
        std::string newStateName = {GetNewLetter(newEquivalentStates.begin()->second.at(0))};

        auto index = 0;
        for (auto transition = newEquivalentStates.begin(); transition != newEquivalentStates.end(); transition++)
        {
            if (transition->second.at(0) == newStateName.at(0))
            {
                continue;
            }

            auto replacementTransition= transition->second;
            transition->second = newStateName + std::to_string(index);
            index++;

            for (auto sameTransition = transition; sameTransition != newEquivalentStates.end(); sameTransition++)
            {
                if (sameTransition->second == replacementTransition)
                {
                    sameTransition->second = newStateName + std::to_string(std::distance(newEquivalentStates.begin(), transition));
                }
            }
        }

        return newEquivalentStates;
    }
}

Machine MachineMinimizator::MinimizeMealy(const Machine& machine)
{
    MachineWithEquivalentStates newMachine = {machine.inputData, machine.states, machine.machineStates, machine.outputData};
    std::unordered_map<std::string, std::string> transitionsForEquivalentStates;
    int inputsCount = newMachine.inputData.size();
    int statesCount = newMachine.states.size();

    for (auto indexI = 0; indexI < statesCount; indexI++)
    {
        std::string states;
        for (auto indexJ = 0; indexJ < inputsCount; indexJ++)
        {
            states += *machine.machineStates.at(indexJ).at(indexI).outputData;
        }
        transitionsForEquivalentStates.emplace(std::pair<std::string, std::string>{newMachine.states.at(indexI), states});
    }

    newMachine.equivalentStates = CreateNewEquivalentStates(transitionsForEquivalentStates);

    return newMachine;
}

Machine MachineMinimizator::MinimizeMoore(const Machine& machine)
{
    return {};
}
