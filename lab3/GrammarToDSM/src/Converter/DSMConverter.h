#pragma once

#include "../Machine/Machine.h"

class DSMConverter
{
public:
    static Machine ConvertToDSM(const Machine& originMachine);
};
