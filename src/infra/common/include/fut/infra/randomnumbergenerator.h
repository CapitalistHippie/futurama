#ifndef FUTURAMA_FUT_INFRA_RANDOMNUMBERGENERATOR_H_INCLUDED
#define FUTURAMA_FUT_INFRA_RANDOMNUMBERGENERATOR_H_INCLUDED

#include <random>

namespace fut::infra
{
class RandomNumberGenerator
{
  private:
    std::default_random_engine rng;

    unsigned int seed;

  public:
    RandomNumberGenerator();
    RandomNumberGenerator(unsigned int seed);

    void Seed(unsigned int seed);
    unsigned int GetSeed() const;

    unsigned int GenerateBetweenInclusive(unsigned int min, unsigned int max);
}; // class RandomNumberGenerator
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_RANDOMNUMBERGENERATOR_H_INCLUDED
