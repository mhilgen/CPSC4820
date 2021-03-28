/*
Name: Max Hilgenberg
Class: 4820
Assignment 1
Date: 01/12/2021
*/


#ifndef PPM_H
#define PPM_H

#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
        char            *name;  // filename
        int             cols;   // width
        int             rows;   // height
        int             maxc;   // max color (usually 255)
        char            *magic; // magic number (expect 'P5')
        float           *rpix;  // red pixels, stored as 1D array
        float           *gpix;  // green pixels, stored as 1D array
        float           *bpix;  // blue pixels, stored as 1D array

} PPM;

PPM     *ppm_alloc(int r, int c);
void     ppm_free(PPM **img);
PPM     *ppm_read(const char *file);
int      ppm_write(PPM *img, const char *file);
PGM     *ppm_white(PPM *img);
#endif