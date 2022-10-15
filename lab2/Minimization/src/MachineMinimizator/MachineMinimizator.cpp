#include "MachineMinimizator.h"

#include "unordered_map"
#include "../Common/Lettering.h"
#include <stdexcept>
#include <set>

namespace
{
    using StateToTransition = std::unordered_map<std::string, std::string>;

    struct MachineWithEquivalentStates : public Machine
    {
        StateToTransition equivalentStates;
    };

    StateToTransition CreateNewEquivalentStates(const StateToTransition& transitionsForEquivalentStates, const StateToTransition& oldEquivalentStates)
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

            auto equivalentStateOfInitiator = oldEquivalentStates.find(transition->first);

            for (auto sameTransition = transition; sameTransition != newEquivalentStates.end(); sameTransition++)
            {
                auto equivalentStateOfCurrent = oldEquivalentStates.find(sameTransition->first);

                if (sameTransition->second == replacementTransition && (equivalentStateOfInitiator == oldEquivalentStates.end()
                    || equivalentStateOfInitiator->second == equivalentStateOfCurrent->second))
                {
                    sameTransition->second = newStateName + std::to_string(std::distance(newEquivalentStates.begin(), transition));
                }
            }
        }

        return newEquivalentStates;
    }

    StateToTransition GetTransitionsToStates(const MachineWithEquivalentStates& machine)
    {
        StateToTransition transitionsForEquivalentStates;
        int inputsCount = machine.inputData.size();
        int statesCount = machine.states.size();

        for (auto indexI = 0; indexI < statesCount; indexI++)
        {
            std::string states;
            for (auto indexJ = 0; indexJ < inputsCount; indexJ++)
            {
                states += machine.machineStates.at(indexJ).at(indexI).state;
            }
            transitionsForEquivalentStates.emplace(std::pair<std::string, std::string>{machine.states.at(indexI), states});
        }

        return transitionsForEquivalentStates;
    }

    int GetCountOfEquivalentStates(const MachineWithEquivalentStates& machine)
    {
        std::set<std::string> equivalentStates;
        for (const auto& equivalentState : machine.equivalentStates)
        {
            equivalentStates.insert(equivalentState.second);
        }

        return equivalentStates.size();
    }
}

Machine MachineMinimizator::MinimizeMealy(const Machine& machine)
{
    MachineWithEquivalentStates newMachine = {machine.inputData, machine.states, machine.machineStates, machine.outputData};
    StateToTransition transitionsForEquivalentStates;
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

    newMachine.equivalentStates = CreateNewEquivalentStates(transitionsForEquivalentStates, newMachine.equivalentStates);

    SetTransitionWithNewEquivalentStates(newMachine, machine);
    MinimizeMachine(newMachine, machine);

    return newMachine;
}

Machine MachineMinimizator::MinimizeMoore(const Machine& machine)
{
    MachineWithEquivalentStates newMachine = {machine.inputData, machine.states, machine.machineStates, machine.outputData};
    //create equivalentStates
    SetTransitionWithNewEquivalentStates(newMachine, machine);
    MinimizeMachine(newMachine, machine);
    return newMachine;
}

void MachineMinimizator::MinimizeMachine(MachineWithEquivalentStates& machine, const Machine& originMachine)
{
    int countOfEquivalentStates = 0;
    int currentCountOfEquivalentStates = GetCountOfEquivalentStates(machine);
    while (countOfEquivalentStates != currentCountOfEquivalentStates && currentCountOfEquivalentStates != machine.states.size())
    {
        auto transitionsForEquivalentStates = GetTransitionsToStates(machine);
        machine.equivalentStates = CreateNewEquivalentStates(transitionsForEquivalentStates, machine.equivalentStates);
        SetTransitionWithNewEquivalentStates(machine, originMachine);
        countOfEquivalentStates = currentCountOfEquivalentStates;
        currentCountOfEquivalentStates = GetCountOfEquivalentStates(machine);
    }

    CreateNewMachineByEquivalentStates(machine, originMachine);
}

void MachineMinimizator::SetTransitionWithNewEquivalentStates(MachineWithEquivalentStates& machine, const Machine& originMachine)
{
    int inputsCount = machine.inputData.size();
    int statesCount = machine.states.size();

    for (auto indexJ = 0; indexJ < statesCount; indexJ++)
    {
        auto currentState = machine.states.at(indexJ);

        for (auto indexI = 0; indexI < inputsCount; indexI++)
        {
            auto originState = originMachine.machineStates.at(indexI).at(indexJ).state;
            auto it = machine.equivalentStates.find(originState);

            if (it == machine.equivalentStates.end())
            {
                throw std::runtime_error("");
            }

            machine.machineStates.at(indexI).at(indexJ).state = it->second;
            machine.machineStates.at(indexI).at(indexJ).outputData = originMachine.machineStates.at(indexI).at(indexJ).outputData;
        }
    }
}

void MachineMinimizator::CreateNewMachineByEquivalentStates(MachineWithEquivalentStates& machine, const Machine& originMachine)
{

}
