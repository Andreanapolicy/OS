#pragma once

#include <string>

char GetRandomLetter(const char letter)
{
    return (letter + 1) % 26;
}