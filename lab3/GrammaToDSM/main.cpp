#include <iostream>
#include "src/Args/ArgsParser.h"

int main(int argc, char* argv[])
{
    auto args = ArgsParser::Parse(argc, argv);
    if (!args)
    {
        std::cout << "Wrong usage. Example: .exe left left-type-grammar.txt output.csv" << std::endl;
        return 1;
    }

    return 0;
}
