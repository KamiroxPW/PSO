#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "pso.h"

char* arg(int n, char **v, char *flag)
{
	for (int i = 2; i < n; i++)
	{
		if(strcmp(v[i], flag) == 0)
		{

			if(i + 1 < n)
			{
				return v[i + 1];
			}
			else
			{
				return NULL; 
			}
		}
	}
	return NULL;
}

int load_config(char *config, PSOParams *params)
{
	FILE *f = fopen(config, "r");
	if (!f) {
		return -1;
	}
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