#ifndef LOGGER_H
#define LOGGER_H
#include "pso.h"

void logcheck(char *name);

void log(const char *filename, int iteration, Swarm *swarm);

#endif