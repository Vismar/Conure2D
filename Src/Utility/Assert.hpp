#pragma once
#include <iostream>

#define Assert(rightCondition, reason)                       \
if (!(rightCondition))                                       \
{                                                       \
    AssertFail(#rightCondition, __FILE__, __LINE__, reason); \
}

void AssertFail(const char* rightCondition, const char* file, int line, const char* reason);