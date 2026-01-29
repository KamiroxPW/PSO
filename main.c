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
	if(argc < 2)
	{
		printf("Uzycie: <map> -p particle_count -i iterations -c config_file -n log_interval\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	Map *map = map_load(f);
	int p_count = atoi(arg(argc, argv, "-p"));
	if(p_count == 0)
		p_count = 30; 
	int iter = atoi(arg(argc, argv, "-i"));
	if(iter == 0)
		iter = 100;
	char *config = arg(argc, argv, "-c");
	int log = atoi(arg(argc, argv, "-n"));
	PSOParams params = {0.5, 1.0, 1.0};
	if(config != NULL)
	{
		printf("Wczytywanie konfiguracji z pliku\n");
		load_config(config, &params);
	}

	printf("Start: Map %dx%d, Particles %d, Iterations %d\n",map->width, map->height, p_count, iter);
	srand(time(NULL));
	Swarm *swarm = swarm_init(p_count, map, params);
	remove("log.csv");
	if(log > 0 && log < iter)
		log_init("log.csv");
	for(int i = 0; i < iter; i++)
	{
		swarm_update(swarm, map);

		if(log > 0 && (i % log == 0))
			log_save("log.csv", i, swarm);
	}

	printf("Znaleziony cel: (%.2f, %.2f) z wartoscia %.2f\n",swarm->gBest_x, swarm->gBest_y, swarm->gBest_val);
	
	fclose(f);
	swarm_free(swarm);
	map_free(map);

	return 0;
}