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


Swarm* swarm_init(int count, Map *map, PSOParams params);

void swarm_update(Swarm *swarm, Map *map);

void swarm_free(Swarm *swarm);

#endif