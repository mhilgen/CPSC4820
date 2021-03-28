#ifndef FILTER_H
#define FILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "pgm.h"

typedef struct{
    //int     rows;
    //int     cols;
    float   *dx;
    float   *dy;
    //int *num;
} FLTR;

FLTR    *make_filter(int num);
void    free_filter(FLTR **img);
//FLTR    *alloc_filter(int r, int c);
#endif