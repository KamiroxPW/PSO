#ifndef LOGGER_H
#define LOGGER_H
#include "pso.h"

void log_init(char *fname);

void log_save(char *fname, int iter, Swarm *swarm);

#endif