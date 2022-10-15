#pragma once

#include <string>
#include "../Machine/Machine.h"

struct Args
{
    MachineType machineType;
    std::string inputFile;
    std::string outputFile;
};