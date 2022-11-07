#pragma once

#include <sstream>
#include "../Machine/Machine.h"

class CSVTextParser
{
public:

    static Machine GetMachine(std::istream& istream);
//    static Machine GetMealy(std::istream& istream)
//    {
//        Machine machine = {};
//
//        ProcessTypicalMachineInputData(istream, machine);
//
//        return machine;
//    }
//
//    static Machine GetMoore(std::istream& istream)
//    {
//        Machine machine = {};
//
//        ProcessSpecificMachineInputData(istream, machine);
//        ProcessTypicalMachineInputData(istream, machine);
//
//        return machine;
//    }

private:
    void static ProcessTypicalMachineInputData(std::istream& istream, Machine& machine);

    void static ProcessSpecificMachineInputData(std::istream& istream, Machine& machine);

    void static FillMachineStateTransitions(Machine& machine, std::vector<std::string>& transitions);

    void static ParseLine(std::string& line, std::vector<std::string>& states);
};