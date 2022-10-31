#pragma once

#include <vector>
#include <set>
#include <string>

struct MachineState
{
    std::set<std::string> states;
    bool isFinal = false;

    bool operator==(const MachineState& machineState) const
    {
        return this->states == machineState.states && this->isFinal == machineState.isFinal;
    }
};

struct Machine
{
    std::vector<std::string> inputData;
    std::vector<std::string> states;
    std::vector<std::vector<MachineState>> machineStates;
};

constexpr auto DEFAULT_FINAL_STATE = "FINAL";