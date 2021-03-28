#ifndef FILTER_H
#define FILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "pgm.h"

typedef struct{
    float   *g;
    float   *h;
    float   *ih;
    float   *ig;
} FLTR;

FLTR    *make_filter();
void    free_filter(FLTR **img);
#endif