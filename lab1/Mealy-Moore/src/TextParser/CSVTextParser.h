#pragma once

#include <sstream>
#include "../Common/Automat.h"

class CSVTextParser
{
public:
    explicit CSVTextParser(const MachineType& machineType)
        : m_machineType(machineType)
    {
    }

    Machine GetData(std::istream& istream)
    {
        Machine machine = {};

        m_machineType == MachineType::Mealy
            ? ProcessMealyInputData(istream, machine)
            : ProcessMooreInputData(istream, machine);

        return machine;
    }

    void SetData(std::ostream& ostream, const Machine& data)
    {
    }

private:
    void ProcessMealyInputData(std::istream& istream, Machine& machine) const
    {
        std::string line;
        std::getline(istream, line);
        std::vector<std::string> parsedLine;
        ParseLine(line, parsedLine);
        std::remove(parsedLine.begin(), parsedLine.end(), "");
        machine.states = parsedLine;

        while (std::getline(istream, line))
        {
            std::vector<std::string> values;
            ParseLine(line, values);

        }
    }

    void ProcessMooreInputData(std::istream& istream, Machine& machine) const
    {

    }

    void ParseLine(std::string& line, std::vector<std::string> states) const
    {
        std::string state;
        std::istringstream ss(line);

        while (std::getline(ss, state, ';'))
        {
            states.push_back(state);
        }
    }

    const MachineType m_machineType;
};