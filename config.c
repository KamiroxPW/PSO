#include <stdio.h>
#include "config.h"
#include "pso.h"

int load_config(FILE *f, PSOParams *params)
{
    if(fscanf(f, "%lf %lf %lf", &params->w, &params->c1, &params->c2) != 3)
    {
        fclose(f);
        return 1;
    }
    return 0;
}