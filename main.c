#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h"
#include "utils.h"

int main(int argc, char **argv)
{
	srand(time(NULL));

	if(argc < 2)
	{
		printf("Brak argumentow");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");	
	int p_count = atoi(argv[2]);
	int iter = atoi(argv[3]);
	FILE *p = fopen(argv[4], "w");
	int log = atoi(argv[5]);

	Map *map = map_load(f);
	PSOParams params = {0.5, 1.0, 1.0};
	if(p)
	{
		if(load_config(p, &params) != 0)
			printf("Blad wczytywania pliku konfiguracyjnego, uzywam domyslnych.\n");
	}

	Swarm *swarm = swarm_init(p_count, map, params);
    
	if(log > 0)
		log_check(argv[4]);

	printf("Start symulacji: Map %dx%d, Particles %d, Iterations %d\n",map->width, map->height, p_count, iter);

	for(int j = 0; j < iter; j++)
	{
		swarm_update(swarm, map);

		if (log > 0 && (j % log == 0))
			log_save(argv[4], j, swarm);
	}

	printf("Znaleziony cel: (%.2f, %.2f) z wartoscia %.2f\n",swarm->gBest_x, swarm->gBest_y, swarm->gBest_val);
	
	fclose(f);
	swarm_free(swarm);
	map_free(map);

	return 0;
}