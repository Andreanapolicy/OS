#pragma once

#include <string>

char GetNewLetter(const char letter)
{
    const char FIRST_TO_USE_LETTER = 'S';
    const char SECOND_TO_USE_LETTER = 'Q';
    return letter == FIRST_TO_USE_LETTER ? SECOND_TO_USE_LETTER : FIRST_TO_USE_LETTER;
}