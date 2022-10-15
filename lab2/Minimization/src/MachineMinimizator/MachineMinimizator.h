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
    static void MinimizeMachine(Machine& machine);

    static void SetTransitionWithNewEquivalentStates(MachineWithEquivalentStates& machine, const Machine& originMachine);
};