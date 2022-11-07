#include "CSVTextParser.h"
#include "../Common/Lettering.h"

namespace
{
    void ParseLine(std::string& line, std::vector<std::string>& states)
    {
        std::string state;
        std::istringstream ss(line);

        while (std::getline(ss, state, ';'))
        {
            states.push_back(state);
        }
    }
}

void CSVTextParser::ProcessTypicalMachineInputData(std::istream& istream, Machine& machine)
{
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> parsedLine;
    ParseLine(line, parsedLine);
    parsedLine.erase(parsedLine.begin());
    for (const auto& value : parsedLine)
    {
        machine.states.push_back({value, false});
    }

    while (std::getline(istream, line))
    {
        std::vector<std::string> values;
        ParseLine(line, values);
        machine.inputData.push_back(values.at(0));
        values.erase(values.begin());
        FillMachineStateTransitions(machine, values);
    }
}

size_t CSVTextParser::GetFinalStatePosition(std::istream& istream)
{
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> parsedLine;
    ParseLine(line, parsedLine);
    parsedLine.erase(parsedLine.begin());
    auto it = std::find(parsedLine.begin(), parsedLine.end(), FINAL_STATE_LETTER);

    return std::distance(parsedLine.begin(), it);
}

void CSVTextParser::FillMachineStateTransitions(Machine& machine, std::vector<std::string>& transitions)
{
    std::vector<MachineState> machineStates;

    for (const auto& transition : transitions)
    {
        MachineState state;
        auto index = transition.find("/");
        if (index != std::string::npos)
        {
            state.state = transition.substr(0, index);
            state.outputData = transition.substr(index + 1, transition.length());
        }
        else
        {
            auto it = std::find(machine.states.begin(), machine.states.end(), transition);
            state.state = transition;
            state.outputData = machine.outputData.at(std::distance(machine.states.begin(), it));
        }
        machineStates.push_back(state);
    }

    machine.machineStates.push_back(machineStates);
}

Machine CSVTextParser::GetMachine(std::istream& istream)
{
    Machine machine = {};

    auto finalStatePos = GetFinalStatePosition(istream);
    ProcessTypicalMachineInputData(istream, machine);

    machine.states.at(finalStatePos).isFinal = true;

    return machine;
}
