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
		printf("Uzycie: <map> -p particle_count -i iterations -c config_file -l log_interval\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	int p_count = atoi(arg(argc, argv, "-p"));
	if(p_count == 0)
		p_count = 30; 
	int iter = atoi(arg(argc, argv, "-i"));
	if(iter == 0)
		iter = 100;
	char *config = arg(argc, argv, "-c");
	int log = atoi(arg(argc, argv, "-l") ? arg(argc, argv, "-l") : "0");

	Map *map = map_load(f);
	PSOParams params = {0.5, 1.0, 1.0};
	if(atoi(config) != -1)
	{
		if(load_config(config, &params) != 0)
			printf("Blad wczytywania pliku konfiguracyjnego, uzywam domyslnych.\n");
	}

	Swarm *swarm = swarm_init(p_count, map, params);
    
	if(log > 0)
		log_check(config);

	printf("Start symulacji: Map %dx%d, Particles %d, Iterations %d\n",map->width, map->height, p_count, iter);

	for(int j = 0; j < iter; j++)
	{
		swarm_update(swarm, map);

		if (log > 0 && (j % log == 0))
			log_save("log", j, swarm);
	}

	printf("Znaleziony cel: (%.2f, %.2f) z wartoscia %.2f\n",swarm->gBest_x, swarm->gBest_y, swarm->gBest_val);
	
	fclose(f);
	swarm_free(swarm);
	map_free(map);

	return 0;
}