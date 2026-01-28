#ifndef LOGGER_H
#define LOGGER_H
#include "pso.h"

void log_check(char *name);

void log_save(const char *filename, int iteration, Swarm *swarm);

#endif