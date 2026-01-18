#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

void logger_init(const char *filename);

void logger_save_iteration(const char *filename, int iteration, Swarm *swarm);

#endif