#include <iostream>
#include "src/Args/ArgsParser.h"
#include "src/Converter/DSMConverter.h"
#include "src/MachineSaver/MachineSaver.h"
#include "src/TextParser/CSVTextParser.h"
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
        std::cout << "Wrong usage. Example: .exe left left-type-grammar.txt output.csv" << std::endl;
        return 1;
    }

    std::ifstream input;
    std::ofstream output;
    if (!PrepareStreams(input, output, *args))
    {
        return 1;
    }
    MachineSaver machineSaver;

    machineSaver.Save(output, DSMConverter::ConvertToDSM(CSVTextParser::GetMachine(input)));

    return 0;
}
