#include <stdio.h>
#include "logger.h"

void logger_init(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f)
    {
        fprintf(f, "iter,particle_id,x,y,fitness\n");
        fclose(f);
    }
}

void logger_save_iteration(const char *filename, int iteration, Swarm *swarm)
{
    FILE *f = fopen(filename, "a");
    if (!f) return;

    for (int i = 0; i < swarm->particle_count; i++)
    {
        fprintf(f, "%d,  %d  ,%.2f  ,%.2f  ,%.2f\n", 
                iteration, i, 
                swarm->particles[i].x, 
                swarm->particles[i].y, 
                swarm->particles[i].fitness);
    }
    fclose(f);
}