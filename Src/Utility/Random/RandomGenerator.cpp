#include "RandomGenerator.hpp"

using namespace Utility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RandomGenerator::RandomGenerator()
: _seed(std::random_device()())
, _mtEngine(_seed)
, _mtEngine64(_seed)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RandomGenerator& RandomGenerator::Instance() 
{
    static RandomGenerator randomGenerator;
    return randomGenerator;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomGenerator::SetSeed(const uint32_t seed)
{
    _seed = seed;
    _mtEngine.seed(_seed);
    _mtEngine64.seed(_seed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t RandomGenerator::GetSeed() const
{
    return _seed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t RandomGenerator::Get()
{
    return _mtEngine();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t RandomGenerator::Get64()
{
    return _mtEngine64();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////