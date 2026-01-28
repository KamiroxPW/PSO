#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "pso.h"

int load_config(FILE *f, PSOParams *params)
{
	if(fscanf(f, "%lf %lf %lf", &params->w, &params->c1, &params->c2) != 3)
	{
		fclose(f);
		return 1;
	}
	return 0;
}

double random_01()
{
	return (double)rand() / (double)RAND_MAX;
}

double random_range(double min, double max)
{
	return min + random_01() * (max - min);
}