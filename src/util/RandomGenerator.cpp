#include "RandomGenerator.h"

#include <algorithm>


random_device RandomNumberGenerator::rd;
mt19937_64 RandomNumberGenerator::mersenne = mt19937_64(rd());
uniform_int_distribution<uint64_t> RandomNumberGenerator::uniform = uniform_int_distribution<uint64_t>(0, UINT64_MAX);

uint64_t RandomNumberGenerator::getRandomNumber()
{
    return uniform(mersenne);
}

void RandomNumberGenerator::getUniqueRandomNumbers(uint64_t n, vector<uint64_t>& numbers)
{
    numbers = vector<uint64_t>(n);
    iota(numbers.begin(), numbers.end(), 0);
    shuffle(numbers.begin(), numbers.end(), mersenne);
}

