#pragma once

#include <vector>
#include <string>

struct MachineState
{
    std::string state;
    bool isFinal = false;

    bool operator==(const MachineState& machineState) const
    {
        return this->state == machineState.state && this->isFinal == machineState.isFinal;
    }
};

struct Machine
{
    std::vector<std::string> inputData;
    std::vector<std::string> states;
    std::vector<std::vector<MachineState>> machineStates;
};