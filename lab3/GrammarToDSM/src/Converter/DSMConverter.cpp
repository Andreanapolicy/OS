#include "DSMConverter.h"
#include "../Common/Lettering.h"
#include <queue>
#include <set>
#include <unordered_map>
#include <iostream>

namespace
{
    using DeterminationState = std::set<std::string>;

    struct DeterminationMachine
    {
        std::vector<std::string> inputData;
        std::vector<DeterminationState> states;
        std::vector<std::vector<dev::MachineState>> machineStates;
    };

    void LogNewStates(const std::unordered_map<std::string, DeterminationState>& states)
    {
        for (const auto& state : states)
        {
            std::cout << state.first << " = ";

            for (const auto& compoundState : state.second)
            {
                std::cout << compoundState << " ";
            }
        }

        std::cout << std::endl;
    }

    void InitClientMachine(const DeterminationMachine& originMachine, client::Machine& newMachine)
    {
        newMachine.inputData = originMachine.inputData;
        for (auto indexI = 0; indexI < originMachine.inputData.size(); indexI++)
        {
            newMachine.machineStates.emplace({});

            for (auto indexJ = 0; indexJ < originMachine.states.size(); indexJ++)
            {
                newMachine.machineStates.at(indexI).push_back({});
            }
        }
    }

    client::Machine ConvertDeterminationMachine(const DeterminationMachine& machine, const std::vector<DeterminationState>& states)
    {
        client::Machine newMachine;
        InitClientMachine(machine, newMachine);

        std::unordered_map<std::string, DeterminationState> newStatesNameMap;
        for (auto index = 0; index < states.size(); index++)
        {
            newStatesNameMap.emplace(NEW_STATE_LETTER + std::to_string(index), states[index]);
        }
        LogNewStates(newStatesNameMap);

        for (auto indexI = 0; indexI < machine.states.size(); indexI++)
        {
            auto it = std::find_if(newStatesNameMap.begin(), newStatesNameMap.end(), [&](const std::pair<std::string, DeterminationState>& element){
                return element.second == machine.states.at(indexI);
            });

            if (it != newStatesNameMap.end())
            {
                newMachine.states.at(indexI).isFinal = it->second.contains(DEFAULT_FINAL_STATE);
                newMachine.states.at(indexI).states = it->first;
            }
        }

        for (auto indexI = 0; indexI < machine.inputData.size(); indexI++)
        {
            for (auto indexJ = 0; indexJ < machine.states.size(); indexJ++)
            {
                auto it = std::find_if(newStatesNameMap.begin(), newStatesNameMap.end(), [&](const std::pair<std::string, DeterminationState>& element){
                    return element.second == machine.machineStates.at(indexI).at(indexJ).states;
                });

                if (it != newStatesNameMap.end())
                {
                    newMachine.machineStates.at(indexI).at(indexJ) = it->first;
                }
            }
        }

        return newMachine;
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
                    transitionStates.emplace_back(dev::MachineState{DeterminationState(), false});
                }
            }
        }
    }

    void MergeTransition(dev::MachineState& destinationState, const dev::MachineState& stateToMerge)
    {
        auto temp = stateToMerge.states;
        destinationState.states.merge(temp);
        destinationState.isFinal = stateToMerge.isFinal || destinationState.isFinal;
    }

    void DetermineState(DeterminationMachine& newMachine, const dev::Machine& originMachine, const DeterminationState& processingStates)
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

    void InitDeterminationMachine(DeterminationMachine& newMachine, const dev::Machine& originMachine)
    {
        newMachine.inputData = originMachine.inputData;
        for (auto index = 0; index < newMachine.inputData.size(); index++)
        {
            newMachine.machineStates.emplace_back();
        }
    }
}

client::Machine DSMConverter::ConvertToDSM(const dev::Machine& originMachine)
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

    return ConvertDeterminationMachine(newMachine, statesToDetermination);
}
