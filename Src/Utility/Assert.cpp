#include "Assert.hpp"

void AssertFail(const char* rightCondition, const char* file, int line, const char* reason)
{
    std::cerr << "Assertion failed"
              << "\n\tExpected: " << rightCondition
              << "\n\tReason: " << reason
              << "\n\tAt: " << file << ":" << line << std::endl;
    abort();
}