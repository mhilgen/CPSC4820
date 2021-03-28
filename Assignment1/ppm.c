/*
Name: Max Hilgenberg
Class: 4820
Assignment 1
Date: 01/12/2021
*/

#include "ppm.h"
#include "pgm.h"

PPM *ppm_alloc(int r, int c){
    PPM *img = NULL;
    img = (PPM *)malloc(sizeof(PPM));
    //making the input into the actual structured variables 
    img->rows = r;
    img->cols = c;
    //since it is a color image I will be having 3 arrays to store the r g b independently
    img->rpix = (float *)malloc((r*c)*sizeof(float));
    img->gpix = (float *)malloc((r*c)*sizeof(float));
    img->bpix = (float *)malloc((r*c)*sizeof(float));
    img->maxc = 255;
    img->magic = (char *)malloc(3*sizeof(char));
    //helps the program to see that it is a color image 
    strcpy(img->magic, "P6");
    return img;
}
void ppm_free(PPM **img){
    //freeing each allocated memory after usage 
    if((*img)->rpix){
        free((*img)->rpix);
    }
    if((*img)->gpix){
        free((*img)->gpix);
    }
    if((*img)->bpix){
        free((*img)->bpix);
    }
    if((*img)->magic){
        free((*img)->magic);
    }
}

PPM *ppm_read(const char *file){
    int i,j;
    int rows, cols, maxc;
    char color;
    PPM *img = NULL;
    FILE *input = NULL;
    unsigned char rpix;
    unsigned char gpix;
    unsigned char bpix;
    //reads the file with binary inclusion
    input = fopen(file, "rb");
    //checks if the header is the right color image with P6
    if(((color = fgetc(input)) == 'P') && ((color = fgetc(input)) == '6') && ((color = fgetc(input)) == '\n')){
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
        img = ppm_alloc(rows, cols);
        if(img){
            for(i = 0; i < rows; i++){
                for(j = 0; j < cols; j++){
                    //checks per pixel if the rows are right 
                    if((fread(&rpix, sizeof(unsigned char), 1, input) < 1) || (fread(&gpix, sizeof(unsigned char), 1, input) < 1) || (fread(&bpix, sizeof(unsigned char), 1, input) < 1) || feof(input)){
                        fprintf(stderr, "Error getting r from %s\n", file);
                    }
                    //stores the r g b pixels into the image arrays which are reduced to decimals since / by maxc (255)
                    img->rpix[i*img->cols + j] = (float)rpix/(float)maxc;
                    img->gpix[i*img->cols + j] = (float)gpix/(float)maxc;
                    img->bpix[i*img->cols + j] = (float)bpix/(float)maxc;
                }
            }
            //printf("Rpix %f, Gpix %f, Bpix %f\n", img->rpix, img->gpix, img->bpix);
        }
    }
    return img;
}
int ppm_write(PPM *img, const char *file){
    int i,j; 
    FILE *output;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    output = fopen(file, "w");
    //checks if the file imported works 
    if(!output){
        printf("Error in opening %s", file);
        return 1;
    }
    //prints the header for the output file (grey.pgm)
    fprintf(output, "%s\n%d %d\n%d\n", img->magic, img->rows, img->cols, img->maxc);
    //printf("%s\n%d %d\n%d\n", img->magic, img->rows, img->cols, img->maxc);
    //goes through the rows and columns again to write out the r g b into the output file 
    for(i = 0; i < img->rows; i++){
        for(j = 0; j < img->cols; j++){
            //copies the colors over and multiplies it again by maxc 
            red = (unsigned char)(img->rpix[i*img->cols + j] * (float)img->maxc);
            //writes it into the output file, pixel by pixel
            fwrite(&red, sizeof(unsigned char), 1, output);
            green = (unsigned char)(img->gpix[i*img->cols + j] * (float)img->maxc);
            fwrite(&green, sizeof(unsigned char), 1, output);
            blue = (unsigned char)(img->bpix[i*img->cols + j] * (float)img->maxc);
            fwrite(&blue, sizeof(unsigned char), 1, output);
        }
    }
    fflush(output);
    fclose(output);
    return 0;
}
PGM *ppm_white(PPM *img){
    //greyscales the pixels using the equation 0.21 R + 0.72 G + 0.07 B
    int i, j;
    PGM *goutput = NULL;
    float r, g, b, x;
    //allocates the memory for the goutput via PGM_alloc
    goutput = pgm_alloc(img->rows, img->cols);
    for(i = 0; i < img->rows; i++){
        for(j = 0; j < img->cols; j++){
            //copies over the r g b values from ppm_write
            r = img->rpix[i*img->cols + j];
            g = img->gpix[i*img->cols + j];
            b = img->bpix[i*img->cols + j];
            //adds them up to grey value for .pgm with the right equation 
            //x = r/3 + g/3 + b/3;
            x = (0.21 * r) + (0.72 * g) + (0.07 * b);
            //sends the information to PGM
            goutput->greypix[i*goutput->cols + j] = x;
        }
    }
    //printf("R: %f\tG: %f\tB: %f\tX: %f", r, g, b, x);
    return goutput;
}