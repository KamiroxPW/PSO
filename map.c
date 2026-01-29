#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map* map_load(FILE *f)
{
	if(!f)
	{
		perror("Nie mozna otworzyc mapy");
		return NULL;
	}

	Map *map = malloc(sizeof(Map));
	if(fscanf(f, "%d %d", &map->width, &map->height) != 2)
	{
		free(map);
		return NULL;
	}

	map->data = malloc(map->height * sizeof(double*));
	if(!map->data)
	{
		free(map);
		return NULL;
	}

	for(int i = 0; i < map->height; i++)
	{
		map->data[i] = malloc(map->width * sizeof(double));
		if(!map->data[i])
		{
			for(int j = 0; j < i; j++)
				free(map->data[j]);
			free(map->data);
			free(map);
			return NULL;
		}
		
		for(int j = 0; j < map->width; j++)
		{
			fscanf(f, "%lf", &map->data[i][j]);
		}
	}

	return map;
}

void map_free(Map *map)
{
	for(int i = 0; i < map->height; i++)
		free(map->data[i]);
	free(map->data);
	free(map);
}

double map_value(Map *map, double x, double y)
{
	if(x >= map->width || y >= map->height || x < 0 || y < 0)
		return -100.0;
	else
	{
		int col = (int)x;
		int row = (int)y;
		return map->data[row][col];
	}
}