#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <fstream>
#include "src/Common/Automat.h"
#include "src/TextParser/CSVTextParser.h"

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

void FillMachine(Machine& machine, const Args& args)
{

}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Wrong usage. Example: .exe mealy-to-moore input.csv output.csv" << std::endl;
        return 1;
    }

    auto textParser = std::make_unique<CSVTextParser>(args->machineType);

    std::ifstream input;
    input.open(args->inputFile);

    if (!input.is_open())
    {
        std::cout << "Input file couldn't be opened" << std::endl;
        return 1;
    }

    std::ofstream output;
    output.open(args->outputFile);

    if (!output.is_open())
    {
        std::cout << "Output file couldn't be opened" << std::endl;
        return 1;
    }

    Machine machine = textParser->GetData(input);

    return 0;
}
