/*
Name: Max Hilgenberg
Class: 4820
Assignment 1
Date: 01/12/2021
*/

#include "pgm.h"

PGM *pgm_alloc(int r, int c){
    PGM *img = NULL;
    img = (PGM *)malloc(sizeof(PGM));
    //making the input into the actual structured variables 
    img->rows = r;
    img->cols = c;
        //since it is a grey image I will only having one 1D array
    img->greypix = (float *)malloc((r*c)*sizeof(float));
    img->maxc = 255;
    img->magic = (char *)malloc(3*sizeof(char));
    //helps the program to see that it is a grey image 
    strcpy(img->magic, "P5");
    return img;
}
void pgm_free(PGM **img){
    //freeing each allocated memory after usage
    if((*img)->greypix){
        free((*img)->greypix);
    }
    if((*img)->magic){
        free((*img)->magic);
    }
}
PGM *pgm_read(const char *file){
    int i,j;
    int rows, cols, maxc;
    char color;
    PGM *img = NULL;
    FILE *input = NULL;
    unsigned char greypix;
    //reads the file with binary inclusio
    input = fopen(file, "rb");
    //checks if the header is the right grey image with P5
    if(((color = fgetc(input)) == 'P') && ((color = fgetc(input)) == '5') && ((color = fgetc(input)) == '\n')){
        //checks if the image is not well formatted 
        if((color = fgetc(input)) == '#'){
            do{
                color = fgetc(input);
            }while(color != '\n');
        }
        else{
            ungetc(color, input);
        }
        //scans for the rows and columns to make sure that they are all there
        if(fscanf(input, "%u %u", &cols, &rows) < 2){
            fprintf(stderr, "not getting the right height or width from %s\n", file);
        }
        //scans for the right color and helps to end the header, so that the pixels can be stored in the arrays
        if((fscanf(input, "%u\n", &maxc) < 1) || maxc != 255){
            printf("Error getting maxc from %s", file);
        }
        //allocate the right amount of memory for each Array via the rows and columns and the image 
        img = pgm_alloc(rows, cols);
        if(img){
            for(i = 0; i < rows; i++){
                for(j = 0; j < cols; j++){
                    //checks per pixel if the rows are right 
                    if((fread(&greypix, sizeof(unsigned char), 1, input) < 1) || feof(input)){
                        fprintf(stderr, "Error from %s\n", file);
                    }
                //stores the grey pixels into the image arrays which are reduced to decimals since / by maxc (255)
                img->greypix[i*img->cols + j] = (float)greypix/(float)maxc;
                }
            }
        }
    }
    return img;
}
int pgm_write(PGM *img, const char *file){
    int i,j; 
    FILE *output;
    unsigned char grey;
    output = fopen(file, "w");
    //checks if the file imported works 
    if(!output){
        printf("Error in opening %s", file);
        return 1;
    }
    //prints the header for the output file (grey.pgm)
    fprintf(output, "%s\n%d %d\n%d\n", img->magic, img->rows, img->cols, img->maxc);
    //goes through the rows and columns again to write out the r g b into the output file 
    for(i = 0; i < img->rows; i++){
        for(j = 0; j < img->cols; j++){
            //copies the grey pixels over and multiplies it again by maxc
            grey = (unsigned char)(img->greypix[i*img->cols + j] * (float)img->maxc);
            //writes it into the output file, pixel by pixel
            fwrite(&grey, sizeof(unsigned char), 1, output);
        }
    }
    fflush(output);
    fclose(output);
    return 0;
}
void pgm_white(PGM *img){
//making the picture white 
    int i, j;
    for(i = 0; i < img->rows; i++){
        for(j = 0; j < img->cols; j++){
            img->greypix[i*img->cols + j] = 1.0;
        }
    }
}

