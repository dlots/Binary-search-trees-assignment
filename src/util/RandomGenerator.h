#ifndef SEMINAR_LAB2_RANDOM_GENERATOR_H
#define SEMINAR_LAB2_RANDOM_GENERATOR_H

#include <random>
using namespace std;


class RandomNumberGenerator
{
public:
    static uint64_t getRandomNumber();
    static void getUniqueRandomNumbers(uint64_t n, vector<uint64_t>& numbers);

private:
    static random_device rd;
    static mt19937_64 mersenne;
    static uniform_int_distribution<uint64_t> uniform;
};

#endif //SEMINAR_LAB2_RANDOM_GENERATOR_H
