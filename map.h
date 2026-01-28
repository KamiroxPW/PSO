#ifndef MAP_H
#define MAP_H
#include <stdio.h>

typedef struct Map
{
	int width;
	int height;
	double **data;
} Map;

Map* map_load(FILE *f);

void map_free(Map *map);

double map_get_value(Map *map, double x, double y);

#endif