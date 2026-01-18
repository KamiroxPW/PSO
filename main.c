#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h"

int load_config(FILE *f, PSOParams *params)
{
    if(fscanf(f, "%lf %lf %lf", &params->w, &params->c1, &params->c2) != 3)
    {
        fclose(f);
        return 0;
    }
    return 0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    if (argc < 2)
    {
        printf("Uzycie: %s <plik_mapy> -p <n> -i <n> -c <config> -n <log_step>\n", argv[0]);
        return 1;
    }
	FILE *f = fopen(argv[1], "r");
    int particles_count = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    int log_step = 0;

    for(int i = 2; i < argc; i++)
    {
        if(strcmp(argv[i], "-p") == 0 && i + 1 < argc) particles_count = atoi(argv[++i]);
        else if(strcmp(argv[i], "-i") == 0 && i + 1 < argc) iterations = atoi(argv[++i]);
        else if(strcmp(argv[i], "-c") == 0 && i + 1 < argc) f = fopen(argv[++i], "r");
        else if(strcmp(argv[i], "-n") == 0 && i + 1 < argc) log_step = atoi(argv[++i]);
    }

    Map *map = map_load(f);
    if(!map) return 1;

    PSOParams params = {0.5, 1.0, 1.0};
    if (f)
    {
        if (load_config(f, &params) != 0)
            printf("Blad wczytywania pliku konfiguracyjnego, uzywam domyslnych.\n");
    }

    Swarm *swarm = pso_init_swarm(particles_count, map, params);
    
    if (log_step > 0) logger_init("pso_log.csv");

    printf("Start symulacji: Map %dx%d, Particles %d, Iterations %d\n",map->width, map->height, particles_count, iterations);

    for (int t = 0; t < iterations; t++)
    {
        pso_update(swarm, map);

        if (log_step > 0 && (t % log_step == 0))
            logger_save_iteration("pso_log.csv", t, swarm);
    }

    printf("Znaleziony cel: (%.2f, %.2f) z wartoscia %.2f\n",swarm->gBest_x, swarm->gBest_y, swarm->gBest_val);
	
	fclose(f);
    pso_free(swarm);
    map_free(map);

    return 0;
}