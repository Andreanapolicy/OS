#pragma once

#include <string>

template <class T>
class ITextParser
{
public:
    virtual T GetData(std::istream& istream);

    virtual void SetData(std::ostream& ostream, const T& data);

    virtual ~ITextParser() = default;
};