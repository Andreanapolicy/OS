#pragma once

#include <string>
#include "../Common/GrammarType.h"

struct Args
{
    GrammarType grammarType;
    std::string inputFile;
    std::string outputFile;
};