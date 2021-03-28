
#ifndef PGM_H
#define PGM_H
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Filter.h"

typedef struct {
        int             cols;   // width
        int             rows;   // height
        int             maxc;   // max color (usually 255)
        char            *magic; // magic number (expect 'P5')
        float           *greypix;  // grey pixels, stored as 1D array
} PGM;

PGM     *pgm_alloc(int r, int c);
void     pgm_free(PGM **img);
PGM     *pgm_read(const char *file);
PGM     *pgm_conv(PGM *img, FLTR *gp);
int      pgm_write(PGM *img, const char *file);
PGM     *pgm_normalize(PGM *img);
//PGM     *pgm_copy(PGM *img);

#endif