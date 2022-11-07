#pragma once

#include <vector>
#include <string>
#include <set>

struct MachineState
{
    std::string state;
    bool isFinal = false;
};

struct MachineTransitionState
{
    std::set<std::string> state;
};

struct Machine
{
    std::vector<std::string> inputData;
    std::vector<MachineState> states;
    std::vector<std::vector<MachineTransitionState>> machineStates;
};