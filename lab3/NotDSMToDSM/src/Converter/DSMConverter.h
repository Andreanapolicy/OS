#pragma once

#include "../Machine/Machine.h"

class DSMConverter
{
public:
    static client::Machine ConvertToDSM(const dev::Machine& originMachine);
};
