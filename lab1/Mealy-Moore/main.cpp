#include <iostream>
#include <optional>
#include "src/Common/Automat.h"

struct Args
{
    MachineType machineType;
    std::string inputFile;
    std::string outputFile;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args args = {};
    const std::string MEALY_MOORE_COMMAND = "mealy-to-moore";
    const std::string MOORE_MEALY_COMMAND = "moore-to-mealy";

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

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Wrong usage. Example: .exe mealy-to-moore input.csv output.csv" << std::endl;
        return 1;
    }

    return 0;
}
