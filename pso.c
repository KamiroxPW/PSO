#include <stdlib.h>
#include <math.h>
#include "pso.h"
#include "utils.h"

Swarm* swarm_init(int count, Map *map, PSOParams params)
{
    Swarm *swarm = malloc(sizeof(Swarm));
    if (!swarm) 
	{
		fprintf(stderr, "Blad alokacji pamieci\n");
		return NULL; 
	}

    swarm->particle_count = count;
    swarm->params = params;
    swarm->particles = malloc(count * sizeof(Particle));
    if (swarm->particles == NULL) 
	{
		free(swarm);
		return NULL;
	}

    swarm->gBest_val = -100.0; 

    for (int i = 0; i < count; i++)
    {
        swarm->particles[i].x = random_range(0, map->width);
        swarm->particles[i].y = random_range(0, map->height);
        swarm->particles[i].vx = 0.0;
        swarm->particles[i].vy = 0.0;

        double val = map_value(map, swarm->particles[i].x, swarm->particles[i].y);
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

void swarm_update(Swarm *swarm, Map *map)
{
	for (int i = 0; i < swarm->particle_count; i++)
	{
		Particle *p = &swarm->particles[i];

		double r1 = random_01();
		double r2 = random_01();

		p->vx = swarm->params.w * p->vx + swarm->params.c1 * r1 * (p->pBest_x - p->x) + swarm->params.c2 * r2 * (swarm->gBest_x - p->x);

		p->vy = swarm->params.w * p->vy + swarm->params.c1 * r1 * (p->pBest_y - p->y) + swarm->params.c2 * r2 * (swarm->gBest_y - p->y);

		p->x += p->vx;
		p->y += p->vy;

		double current_val = map_value(map, p->x, p->y);
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

void swarm_free(Swarm *swarm)
{
	if(swarm)
	{
		free(swarm->particles);
		free(swarm);
	}
}