#ifndef LOGGER_H
#define LOGGER_H
#include "pso.h"

void log_check(char *fname);

void log_save(char *fname, int iter, Swarm *swarm);

#endif