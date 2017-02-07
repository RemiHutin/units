#pragma once
#include "dimension.h"
#include "fraction.h"
#include "string.h"





template <typename S = String::impl<'\0'>>
class BaseUnit
{
public:
    typedef S symbol;

    static void printSymbol(void)
    {
        S::print();
    }

};
