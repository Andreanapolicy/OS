#include <iostream>
#include "src/Args/ArgsParser.h"
#include "src/TextParser/CSVTextParser.h"
#include "src/MachineSaver/MachineSaver.h"
#include "src/MachineMinimizator/MachineMinimizator.h"

#include <fstream>

bool PrepareStreams(std::ifstream& input, std::ofstream& output, const Args& args)
{
    input.open(args.inputFile);

    if (!input.is_open())
    {
        std::cout << "Input file couldn't be opened" << std::endl;
        return false;
    }

    output.open(args.outputFile);

    if (!output.is_open())
    {
        std::cout << "Output file couldn't be opened" << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    auto args = ArgsParser::Parse(argc, argv);
    if (!args)
    {
        std::cout << "Wrong usage. Example: .exe mealy-to-moore input.csv output.csv" << std::endl;
        return 1;
    }

    std::ifstream input;
    std::ofstream output;
    if (!PrepareStreams(input, output, *args))
    {
        return 1;
    }

    Machine machine;
    if (args->machineType == MachineType::Mealy)
    {
        machine = CSVTextParser::GetMealy(input);
        MachineSaver::SaveMealyMachine(output, MachineMinimizator::MinimizeMealy(machine));
    }
    else
    {
        machine = CSVTextParser::GetMoore(input);
        MachineSaver::SaveMooreMachine(output, MachineMinimizator::MinimizeMoore(machine));
    }

    return 0;
}
