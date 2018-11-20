#include "RNG.h"
#include <random>


RNG::RNG()
{
}


RNG::~RNG()
{
}

int RNG::GetRandomNumber(int iRangeMin, int iRangeMax) {
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(iRangeMin, iRangeMax);
	int generated = distribution(engine);

	return generated;
}