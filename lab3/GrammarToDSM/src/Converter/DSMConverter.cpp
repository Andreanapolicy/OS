#include "DSMConverter.h"
#include "../Common/Lettering.h"
#include <queue>
#include <set>
#include <iostream>

namespace
{
    using DeterminationState = std::set<std::string>;

    struct DeterminationMachine
    {
        std::vector<std::string> inputData;
        std::vector<DeterminationState> states;
        std::vector<std::vector<MachineState>> machineStates;
    };

    void LogNewStates(const DeterminationState& states, const std::string& newState)
    {
        std::cout << newState << " = ";

        for (const auto& state : states)
        {
            std::cout << state << " ";
        }

        std::cout << std::endl;
    }

    Machine ConvertDeterminationMachineToMachine(const DeterminationMachine& machine)
    {
        return {};
    }

    void AddNewStateToMachine(DeterminationMachine& machine, const DeterminationState& newState)
    {
        auto it = std::find(machine.states.begin(), machine.states.end(), newState);

        if (it == machine.states.end())
        {
            machine.states.emplace_back(newState);
            for (auto& transitionStates: machine.machineStates)
            {
                if (transitionStates.size() != machine.states.size())
                {
                    transitionStates.emplace_back(MachineState{DeterminationState(), false});
                }
            }
        }
    }

    void MergeTransition(MachineState& destinationState, const MachineState& stateToMerge)
    {
        auto temp = stateToMerge.states;
        destinationState.states.merge(temp);
        destinationState.isFinal = stateToMerge.isFinal || destinationState.isFinal;
    }

    void DetermineState(DeterminationMachine& newMachine, const Machine& originMachine, const DeterminationState& processingStates)
    {
        for (const auto& state : processingStates)
        {
            size_t stateIndex = std::distance(originMachine.states.begin(), std::find(originMachine.states.begin(), originMachine.states.end(), state));

            for (auto inputDataIndex = 0; inputDataIndex < newMachine.inputData.size(); inputDataIndex++)
            {
                auto transitionCell = originMachine.machineStates.at(inputDataIndex).at(stateIndex);
                MergeTransition(newMachine.machineStates.at(inputDataIndex).at(newMachine.states.size() - 1), transitionCell);
            }
        }
    }

    void FillNewStatesToDetermination(const DeterminationMachine& newMachine, std::vector<DeterminationState>& statesToDetermination)
    {
        for (const auto& transitions : newMachine.machineStates)
        {
            auto newStates = transitions.at(newMachine.states.size() - 1).states;
            if (!newStates.empty() && std::find(statesToDetermination.begin(), statesToDetermination.end(), newStates) == statesToDetermination.end())
            {
                statesToDetermination.push_back(newStates);
            }
        }
    }

    void InitDeterminationMachine(DeterminationMachine& newMachine, const Machine& originMachine)
    {
        newMachine.inputData = originMachine.inputData;
        for (auto index = 0; index < newMachine.inputData.size(); index++)
        {
            newMachine.machineStates.emplace_back();
        }
    }
}

Machine DSMConverter::ConvertToDSM(const Machine& originMachine)
{
    DeterminationMachine newMachine;
    InitDeterminationMachine(newMachine, originMachine);

    std::vector<DeterminationState> statesToDetermination;

    statesToDetermination.push_back({originMachine.states.at(0)}); // just push initial state.

    for (auto index = 0; index < statesToDetermination.size(); index++)
    {
        auto processingStates = statesToDetermination[index];
        AddNewStateToMachine(newMachine, processingStates);
        DetermineState(newMachine, originMachine, processingStates);

        FillNewStatesToDetermination(newMachine, statesToDetermination);
    }

    return ConvertDeterminationMachineToMachine(newMachine);
}
