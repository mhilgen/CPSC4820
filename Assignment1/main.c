/*
Name: Max Hilgenberg
Class: 4820
Assignment 1
Date: 01/12/2021
*/

#include "ppm.h"
#include "pgm.h"

int main(int argc, char *argv[]){
    PPM *input = NULL;
    PGM *output = NULL;
    //sending ppm_read to read the mandrill file
    input = ppm_read("mandrill.ppm");
    //then it gets whitened 
    output = ppm_white(input);
    //and the greyscale vlaues will be written into the grey.pgm file 
    pgm_write(output, "grey.pgm");
    //freeing the memory at the end
    ppm_free(&input);
    pgm_free(&output);
    return 0;
}
