#include <stdio.h>
#include "logger.h"

void log_check(char *fname)
{
	FILE *f = fopen(fname, "r");
	if(f == NULL)
	{
		f = fopen(fname, "w");
	}
	fclose(f);
}

void log_save(char *fname, int iter, Swarm *swarm)
{
	FILE *f = fopen(fname, "a");
	if(!f) return;

	for(int i = 0; i < swarm->particle_count; i++)
	{
		fprintf(f, "%d,  %d  ,%.2f  ,%.2f  ,%.2f\n", iter, i, swarm->particles[i].x, swarm->particles[i].y, swarm->particles[i].fitness);
	}
	fclose(f);
}