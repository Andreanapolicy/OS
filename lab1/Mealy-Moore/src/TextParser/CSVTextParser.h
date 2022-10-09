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

private:
    void ProcessMealyInputData(std::istream& istream, Machine& machine) const
    {
        std::string line;
        std::getline(istream, line);
        std::vector<std::string> parsedLine;
        ParseLine(line, parsedLine);
        parsedLine.erase(parsedLine.begin());
        machine.states = parsedLine;

        while (std::getline(istream, line))
        {
            std::vector<std::string> values;
            ParseLine(line, values);
            machine.inputData.push_back(values.at(0));
            values.erase(values.begin());
            FillMachineStateTransitions(machine, values);
        }
    }

    void ProcessMooreInputData(std::istream& istream, Machine& machine) const
    {

    }

    void FillMachineStateTransitions(Machine& machine, std::vector<std::string>& transitions) const
    {
        std::vector<MachineState> machineStates;

        for (const auto& transition : transitions)
        {
            MachineState state;
            auto it = transition.find("/");
            if (it != std::string::npos)
            {
                state.state = transition.substr(0, it);
                state.outputData = transition.substr(it + 1, transition.length());
            }
            else
            {
                state.state = transition;
            }
            machineStates.push_back(state);
        }

        machine.machineStates.push_back(machineStates);
    }

    void ParseLine(std::string& line, std::vector<std::string>& states) const
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