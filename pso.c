#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "pso.h"
#include "rand.h"

Swarm* pso_init_swarm(int count, Map *map, PSOParams params)
{
	Swarm *swarm = malloc(sizeof(Swarm));
	swarm->particle_count = count;
	swarm->params = params;
	swarm->particles = malloc(count * sizeof(Particle));

	swarm->gBest_val = -DBL_MAX;

	for (int i = 0; i < count; i++)
	{
		swarm->particles[i].x = random_range(0, map->width - 1);
		swarm->particles[i].y = random_range(0, map->height - 1);

		swarm->particles[i].vx = random_range(-1, 1);
		swarm->particles[i].vy = random_range(-1, 1);

		double val = map_get_value(map, swarm->particles[i].x, swarm->particles[i].y);
		swarm->particles[i].fitness = val;

		swarm->particles[i].pBest_x = swarm->particles[i].x;
		swarm->particles[i].pBest_y = swarm->particles[i].y;
		swarm->particles[i].pBest_val = val;

		if(val > swarm->gBest_val)
		{
			swarm->gBest_val = val;
			swarm->gBest_x = swarm->particles[i].x;
			swarm->gBest_y = swarm->particles[i].y;
		}
	}
	return swarm;
}

void pso_update(Swarm *swarm, Map *map)
{
	for (int i = 0; i < swarm->particle_count; i++)
	{
		Particle *p = &swarm->particles[i];

		double r1 = random_01();
		double r2 = random_01();

		p->vx = swarm->params.w * p->vx +
				swarm->params.c1 * r1 * (p->pBest_x - p->x) +
				swarm->params.c2 * r2 * (swarm->gBest_x - p->x);

		p->vy = swarm->params.w * p->vy +
				swarm->params.c1 * r1 * (p->pBest_y - p->y) +
				swarm->params.c2 * r2 * (swarm->gBest_y - p->y);

		p->x += p->vx;
		p->y += p->vy;

		double current_val = map_get_value(map, p->x, p->y);
		p->fitness = current_val;

		if(current_val > p->pBest_val)
		{
			p->pBest_val = current_val;
			p->pBest_x = p->x;
			p->pBest_y = p->y;

			if(current_val > swarm->gBest_val)
			{
				swarm->gBest_val = current_val;
				swarm->gBest_x = p->x;
				swarm->gBest_y = p->y;
			}
		}
	}
}

void pso_free(Swarm *swarm)
{
	if(swarm)
	{
		free(swarm->particles);
		free(swarm);
	}
}