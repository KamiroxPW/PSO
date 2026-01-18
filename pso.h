#ifndef PSO_H
#define PSO_H
#include "map.h"

typedef struct PSOParams
{
	double w;
	double c1;
	double c2;
} PSOParams;

typedef struct Particle
{
	double x, y;
	double vx, vy;
	double pBest_x, pBest_y;
	double pBest_val;
	double fitness;
} Particle;

typedef struct Swarm
{
	Particle *particles;
	int particle_count;
	double gBest_x, gBest_y;
	double gBest_val;
	PSOParams params;
} Swarm;

Swarm* pso_init_swarm(int count, Map *map, PSOParams params);

void pso_update(Swarm *swarm, Map *map);

void pso_free(Swarm *swarm);

#endif