#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "../../Machine/Machine.h"

using namespace dev;

class EmptyStateRemover
{
public:

    using NonEmptyTransitions = std::unordered_map<std::string, std::set<std::string>>;

    NonEmptyTransitions static GenerateNonEmptyTransitions(const Machine& machine);
};
