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

        SetInitialStatesAndOutputData(newMachine, newStates);
        SetInputData(newMachine, machine.inputData);
        SetTransitionData(newMachine, machine, newStates);
        return newMachine;
    }

    Machine static GetMealyMachineFromMoore(const Machine& machine)
    {
        Machine newMachine = machine;

        return newMachine;
    }

private:
    std::map<std::string, MachineState> static CreateMapStates(const Machine& machine)
    {
        std::string newStateName = {GetNewLetter(machine.states.at(0).at(0))};
        std::map<std::string, MachineState> transitionMap;

        for (auto const& transitionLine: machine.machineStates)
        {
            for (auto const& state: transitionLine)
            {
                if (!isValueExist(transitionMap, state))
                {
                    transitionMap.insert(std::make_pair(newStateName + std::to_string(transitionMap.size()), state));
                }
            }
        }

        return transitionMap;
    }

    bool static isValueExist(const std::map<std::string, MachineState>& machineMap, const MachineState& state)
    {
        for (const auto& [key, value]: machineMap)
        {
            if (value == state)
            {
                return true;
            }
        }
        return false;
    }

    void static SetInitialStatesAndOutputData(Machine& machine, const std::map<std::string, MachineState>& newStates)
    {
        for (auto const& state : newStates)
        {
            machine.states.push_back(state.first);
            machine.outputData.push_back(*state.second.outputData);
        }
    }

    void static SetInputData(Machine& machine, const std::vector<std::string>& inputData)
    {
        machine.inputData = inputData;
    }

    void static SetTransitionData(Machine& machine, const Machine& oldMachine, const std::map<std::string, MachineState>& newStates)
    {
        int inputsCount = machine.inputData.size();
        int statesCount = machine.states.size();
        std::vector<MachineState> test(1, MachineState());

        for (auto indexI = 0; indexI < inputsCount; indexI++)
        {
            machine.machineStates.emplace_back(std::vector<MachineState>(statesCount, MachineState()));
        }

        for (auto indexJ = 0; indexJ < statesCount; indexJ++)
        {
            auto stateFrom = machine.states.at(indexJ);
            auto initialStateIt = std::find_if(newStates.begin(), newStates.end(), [&](const std::pair<std::string, MachineState>& element) {
                return element.first == stateFrom;
            });
            auto initialState = initialStateIt->second;

            auto indexOfNewStates = std::distance(oldMachine.states.begin(), std::find(oldMachine.states.begin(), oldMachine.states.end(), initialState.state));

            for (auto indexI = 0; indexI < inputsCount; indexI++)
            {
                auto oldState = oldMachine.machineStates.at(indexI).at(indexOfNewStates);

                auto it = std::find_if(newStates.begin(), newStates.end(), [&](const std::pair<std::string, MachineState>& element) {
                    return element.second == oldState;
                });
                machine.machineStates.at(indexI).at(indexJ).state = it->first;
            }
        }
    }
};