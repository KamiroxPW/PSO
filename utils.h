#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "pso.h"

int load_config(FILE *f, PSOParams *params);

double random_01();

double random_range(double min, double max);

#endif