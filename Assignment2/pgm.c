#include <strings.h>

#include "pgm.h"
#include "Filter.h"
#define MAX(a, b) b < a ? a : b
//allocates the images 
//          cols, rows, array of pixels and magic, maxc
PGM     *pgm_alloc(int r, int c){
    PGM *img = NULL;
    img = (PGM *)malloc(sizeof(PGM));
    img->rows = r;
    img->cols = c;
    img->greypix = (float *)malloc((r*c)*sizeof(float));
    bzero(img->greypix,(r*c)*sizeof(float));
    img->maxc = 255;
    img->magic = (char *)malloc(3*sizeof(char));
    strcpy(img->magic, "P5");
    return img;
}
void     pgm_free(PGM **img){
    //freeing each allocated memory after usage
    if((*img)->greypix){
        free((*img)->greypix);
    }
    if((*img)->magic){
        free((*img)->magic);
    }
}
PGM     *pgm_read(const char *file){
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
                //printf("Read: Image value: %f\n", img->greypix[i]);
                }
            }
        }
    }
    return img;
}
//convolution for pixels 
PGM     *pgm_conv(PGM *img, FLTR *gimage){
    //declaring new images and allocate the memory for it
    PGM *Ximg = NULL;
    PGM *Fimg = NULL;
    PGM *Dimg = NULL;
    Dimg = pgm_alloc(img->rows, img->cols);
    Ximg = pgm_alloc(img->rows, img->cols);
    Fimg = pgm_alloc(img->rows, img->cols);
    int r = img->rows;
    int c = img->cols;
    //loops throught the rows and columns 
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            //goes through the filter position
            for(int m = 0; m < 3; m++){
                //going over the rows for the dx filter
                Ximg->greypix[i*c+j] += gimage->dx[m] * ((i - m) < c ? img->greypix[(i-m)*c+j] : 0.0);
            }
        }
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            //goes through the filter position
            for(int m = 0; m < 3; m++){
                //going over the columns for the dy filter
                Fimg->greypix[i*c+j] += gimage->dy[m] * ((j - m) < c ? Ximg->greypix[i*c+(j-m)] : 0.0);
            }
        }
    }
    //frees the images and returns the Final image
    pgm_free(&Ximg);
    return Fimg;
}
int      pgm_write(PGM *img, const char *file){
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
    //fprintf(stderr, "Header: %s\nR: %d C: %d\nMaxColor: %d\n", img->magic, img->rows, img->cols, img->maxc);
    //goes through the rows and columns again to write out the r g b into the output file 
    for(i = 0; i < img->rows; i++){
        for(j = 0; j < img->cols; j++){
            //printf("Test: %d\n", i);
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
//normalizng the Image before final write up
PGM     *pgm_normalize(PGM *img){
    //declaring a new image with other variables
    PGM *nimg = NULL;
    nimg = pgm_alloc(img->rows, img->cols);
    float maxc = 0;
    float minc = 255;
    float denom;
    int r = img->rows;
    int c = img->cols;
    //going through the columns and rows 
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            //checks each pixel if it is bigger than maxc 
            if(maxc < img->greypix[i*c+j]){
                maxc = img->greypix[i*c+j];
            }
            //checks each pixel if it is smaller than minc 
            if(minc > img->greypix[i*c+j]){
                minc = img->greypix[i*c+j];
            }
        }
    }
    //printf("\nMax: %f\tMin: %f\n", maxc, minc);
    //adds min and max+1
    denom = maxc - minc;
    //gets to the rows and columns 
    for(int k = 0; k < r; k++){
        for(int l = 0; l < c; l++){
            //normalizes the image by color code so that it looks better
            nimg->greypix[k*c+l] = (img->greypix[k*c+l] - minc)/denom;
        }
    }
    //pgm_free(&img);
    return nimg;
}