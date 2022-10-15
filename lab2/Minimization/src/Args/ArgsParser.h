#pragma once

#include <optional>
#include "Args.h"
#include "../Machine/Machine.h"

class ArgsParser
{
public:
    static std::optional<Args> Parse(int argc, char* argv[])
    {
        Args args = {};
        const std::string MEALY_MOORE_COMMAND = "mealy";
        const std::string MOORE_MEALY_COMMAND = "moore";

        if (argc != 4)
        {
            return std::nullopt;
        }

        if (argv[1] == MEALY_MOORE_COMMAND)
        {
            args.machineType = MachineType::Mealy;
        }
        else if (argv[1] == MOORE_MEALY_COMMAND)
        {
            args.machineType = MachineType::Moore;
        }
        else
        {
            return std::nullopt;
        }

        args.inputFile = argv[2];
        args.outputFile = argv[3];
        return args;
    }
};