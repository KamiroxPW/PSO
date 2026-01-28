#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "pso.h"

char* flag(int argc, char **argv, char *flaga)
{
	for (int i = 2; i < argc; i++)
	{
		if(strcmp(argv[i], flaga) == 0)
		{

			if (i + 1 < argc)
			{
				return argv[i + 1];
			}
			else
			{
				return NULL; 
			}
		}
	}
	return NULL;
}

int load_config(FILE *f, PSOParams *params)
{
	fopen(f, "r");
	fscanf(f, "%lf %lf %lf", &params->w, &params->c1, &params->c2);
	fclose(f);
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