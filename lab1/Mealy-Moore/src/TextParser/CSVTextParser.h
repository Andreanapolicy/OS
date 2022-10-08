#pragma once

#include "ITextParser.h"
#include "../Common/Automat.h"

class CSVTextParser : public ITextParser<Machine>
{
public:
    CSVTextParser(const MachineType& machineType)
        : m_machineType(machineType)
    {
    }

    Machine GetData(std::istream& istream) override
    {
        auto machine = new Machine;

        return ITextParser::GetData(istream);
    }

    void SetData(std::ostream& ostream, const Machine& data) override
    {
        return ITextParser::SetData(ostream, data);
    }

private:
    const MachineType m_machineType;
};