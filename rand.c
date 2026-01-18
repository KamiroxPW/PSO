#include <stdlib.h>
#include "rand.h"

double random_01()
{
	return (double)rand() / (double)RAND_MAX;
}

double random_range(double min, double max)
{
	return min + random_01() * (max - min);
}