#include "fut/infra/randomnumbergenerator.h"

#include <chrono>

using namespace fut::infra;

RandomNumberGenerator::RandomNumberGenerator()
{
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    Seed(seed);
}

RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
{
    Seed(seed);
}

void RandomNumberGenerator::Seed(unsigned int seed)
{
    rng.seed(seed);

    this->seed = seed;
}

unsigned int RandomNumberGenerator::GetSeed() const
{
    return seed;
}

unsigned int RandomNumberGenerator::GenerateBetweenInclusive(unsigned int min, unsigned int max)
{
    std::uniform_int_distribution<unsigned int> distribution(min, max);

    return distribution(rng);
}
