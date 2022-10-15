#pragma once

#include "../Machine/Machine.h"

class MachineMinimizator
{
public:
    static Machine MinimizeMoore(const Machine& machine);

    static Machine MinimizeMealy(const Machine& machine);
};