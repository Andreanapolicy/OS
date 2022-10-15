#pragma once

#include "../Machine/Machine.h"

namespace
{
    struct MachineWithEquivalentStates;
}

class MachineMinimizator
{
public:
    static Machine MinimizeMoore(const Machine& machine);

    static Machine MinimizeMealy(const Machine& machine);

private:
    static void MinimizeMachine(MachineWithEquivalentStates& machine, const Machine& originMachine);

    static void SetTransitionWithNewEquivalentStates(MachineWithEquivalentStates& machine, const Machine& originMachine);
    static void CreateNewMachineByEquivalentStates(MachineWithEquivalentStates& machine, const Machine& originMachine);
};