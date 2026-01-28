#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "pso.h"

char* arg(int n, char **v, char *flag);

int load_config(char *config, PSOParams *params);

double random_01();

double random_range(double min, double max);

#endif