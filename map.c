#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "map.h"

Map* map_load(FILE *f)
{
	if(!f)
	{
		perror("Nie mozna otworzyc pliku mapy");
		return NULL;
	}

	Map *map = malloc(sizeof(Map));
	if(fscanf(f, "%d %d", &map->width, &map->height) != 2)
	{
		free(map);
		return NULL;
	}

	map->data = malloc(map->height * sizeof(double*));
	for(int i = 0; i < map->height; i++)
	{
		map->data[i] = malloc(map->width * sizeof(double));
		for(int j = 0; j < map->width; j++)
		{
			fscanf(f, "%lf", &map->data[i][j]);
		}
	}

	return map;
}

void map_free(Map *map)
{
	if(!map) return;
	for(int i = 0; i < map->height; i++)
		free(map->data[i]);
	free(map->data);
	free(map);
}

double map_get_value(const Map *map, double x, double y)
{
	int col = (int)round(x);
	int row = (int)round(y);

	if (col < 0 || col >= map->width || row < 0 || row >= map->height)
		return -1000000.0;

	return map->data[row][col];
}