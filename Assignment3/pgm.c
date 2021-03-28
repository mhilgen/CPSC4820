#include <strings.h>
#include "pgm.h"
#include "Filter.h"
//allocates the images 
//cols, rows, array of pixels and magic, maxc
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
void    pgm_dwt2D(PGM*img, int levels){
    FLTR *wimg = make_filter();
    PGM *Hr = pgm_alloc(img->rows, img->cols);
    PGM *Gr = pgm_alloc(img->rows, img->cols);
    int high = (log10(img->rows))/(log10(2.0));
    int low = high - levels;
    int r = img->rows;
    int c = img->cols;
    int i, j, m, jj, ii;
    int roff = r/2;
    int coff = c/2;
    int r2 = r/2;
    int c2 = c/2;
    
    //printf("High: %d & Low: %d & high-low: %d\n", high, low, (high-low));
    //main loop to go through x amounts of levels
    for(int k = high; k >= low; k--){
        //printf("\t%d loops left!\n", (k-low));
        for(i = 0; i < r; i++){
            for(j = 0; j < c2; j++){
                //zeroing the temp arrays
               Hr->greypix[i*c2+j] = 0.0;
               Gr->greypix[i*c2+j] = 0.0;  
                for(m = 0; m < 18; m++){
                    //adding the wavelet filter to the image for the Hr and Gr image
                    jj = j << 1;
                    Hr->greypix[i*c2+j] += wimg->h[m]*img->greypix[i*r+(jj+m)];
                    Gr->greypix[i*c2+j] += wimg->g[m]*img->greypix[i*r+(jj+m)]; 
                }
            }
        }
        //printf("First Loop Done\n");
        for(i = 0; i < r2; i++){
            for(j = 0; j < c2; j++){
                //emptying the imported image 
                img->greypix[i*r+j] = 0.0;
                img->greypix[(i+roff)*r+j] = 0.0;
                img->greypix[i*r+(j+coff)] = 0.0;
                img->greypix[(i+roff)*r+(j+coff)] = 0.0;
                for(m = 0; m < 18; m++){
                    //printf("i: %d\tj: %d\tm: %d\t", i, j, m);
                    ii = i<<1;
                    //top left
                    img->greypix[i*r+j] += wimg->h[m]*Hr->greypix[(ii+m)*r2+j];
                    //top right
                    img->greypix[(i+roff)*r+j] += wimg->g[m]*Hr->greypix[(ii+m)*r2+j];
                    //bottom left
                    img->greypix[i*r+(j+coff)] += wimg->h[m]*Gr->greypix[(ii+m)*r2+j];
                    //bottom right
                    img->greypix[(i+roff)*r+(j+coff)] += wimg->g[m]*Gr->greypix[(ii+m)*r2+j];
                }
            }
        }
        //reducing the borders for the next level
    r2 = r2/2;
    c2 = c2/2;   
    coff = coff/2;
    roff = roff/2;  
    }
    pgm_free(&Hr);
    pgm_free(&Gr);
     
}
void    pgm_idwt2D(PGM*img, int levels){
    FLTR *wimg = make_filter();
    
    int high = (log10(img->rows))/(log10(2.0));
    int low = high - levels;
    int r = img->rows;
    int c = img->cols;
    PGM *Hr = pgm_alloc(r, c);
    PGM *Gr = pgm_alloc(r, c);
    int i, j, m, jj, ii;
    int roff = r << 1;
    int coff = c << 1;
    int r2 = r >> 1;
    int c2 = c >> 1;
   
    for(int k = high; k >= low; k--){
        for(i = 0; i < r; i++){
            for(j = 0; j < c2; j++){
                ii = i << 1;
                    Hr->greypix[ii*r2+j] += img->greypix[i*c+j];// * wimg->ih[m];
                    //Hr->greypix[(ii+1)*r2+j] += img->greypix[(i+roff)*c+j];// * wimg->ig[m]; 
                    //Gr->greypix[(ii)*r2+j] += img->greypix[i*c+(j+coff)];// * wimg->ih[m];
                    //Gr->greypix[(ii+1)*r2+j] += img->greypix[(i+roff)*c+(j+coff)];// * wimg->ig[m];
                    //printf("\ti: %d, j: %d, m: %d\n", i, j, m);
                //}
            }
        }
        for(i = 0; i < r; i++){
            for(j = 0; j < c; j++){
                jj = j << 1;
                for(m = 0; m < 18; m++){
                    img->greypix[i*r+(jj)] += wimg->ih[m] * Hr->greypix[i*c2+j];
                    img->greypix[i*r+(jj+1)] += wimg->ig[m] * Gr->greypix[i*c2+j];
                }
            }
        }
        r2 = r2*2;
        c2 = c2*2;   
        coff = coff*2;
        roff = roff*2;
    }
    
    //pgm_free(&Hr);
    //pgm_free(&Gr);

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

void      pgm_MSE(PGM *gimg){
    float error;
    float sum; 
    PGM *Originalimg = NULL;
    PGM * Timg = NULL;
    Originalimg = pgm_read("mandrill.pgm");
    Timg = pgm_read("ngrey.pgm");
    int r = Originalimg->rows;
    int c = Originalimg->cols;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            sum += (Originalimg->greypix[i*r+j] - Timg->greypix[i*r+j]);
        }
    }
    error = (1/r)*(pow(sum, 2));
    printf("Sum: %f\tError: %f%%\n", sum, error);
}