#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include "pso.h"

typedef struct DefaultParams
{
	double w;
	double c1;
	double c2;
} DefaultParams;

int load_config(FILE *f, PSOParams *params);

#endif