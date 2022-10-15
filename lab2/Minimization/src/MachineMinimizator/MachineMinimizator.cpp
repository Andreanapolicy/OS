#include "MachineMinimizator.h"

#include "unordered_map"

namespace
{
    struct MachineWithEquivalentStates : public Machine
    {
        std::unordered_map<std::string, MachineState> equivalentStates;
    };

    struct StateToTransitions
    {
        std::string state;
        std::string transitions;
    };
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

    return {};
}

Machine MachineMinimizator::MinimizeMoore(const Machine& machine)
{
    return {};
}
