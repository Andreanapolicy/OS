#pragma once

#include "ITextParser.h"
#include "../Common/Automat.h"

class CSVTextParser : public ITextParser<Machine>
{
public:
    Machine GetData(std::istream& istream) override
    {
        auto machine = new Machine;
        istream
        return ITextParser::GetData(istream);
    }

    void SetData(std::ostream& ostream, const Machine& data) override
    {
        return ITextParser::SetData(ostream, data);
    }
};