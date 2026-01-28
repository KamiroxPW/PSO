#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

void logger_check(char *name);

void logger_save(const char *filename, int iteration, Swarm *swarm);

#endif