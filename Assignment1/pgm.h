/*
Name: Max Hilgenberg
Class: 4820
Assignment 1
Date: 01/12/2021
*/

#ifndef PGM_H
#define PGM_H


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
        float           *greypix;  // grey pixels, stored as 1D array
} PGM;

PGM     *pgm_alloc(int r, int c);
void     pgm_free(PGM **img);
PGM     *pgm_read(const char *file);
int      pgm_write(PGM *img, const char *file);
void     pgm_white(PGM *img);
#endif