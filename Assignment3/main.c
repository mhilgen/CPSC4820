#include "Filter.h"
#include "pgm.h"

int main(int argc,char **argv)
{
        int     levels = 0;
        PGM     *gimg=NULL, *nimg=NULL, *Fimg = NULL;
  //makes the string from command line to a integer for levels
  
  levels = atoi(argv[1]);

  //printf("%d levels\n", levels);
  // allocte image of given size
  //printf("Reading\n");
  gimg = pgm_read("mandrill.pgm");
  
  // perform the DWT transform to given levels, 0 will do 1 level,
  // ilog2(img->rows)-1 should do the full DWT, assuming img is square and POT
//levels = pgm_levels(gimg);
  //printf("DWT2D\n");
  pgm_dwt2D(gimg,levels);
  pgm_write(gimg,"dgrey.pgm");

  // copy DWT image and normalize, for visualization purposes
  //nimg = pgm_copy(gimg);
 // printf("Normalize\n");
  nimg = pgm_normalize(gimg);
  pgm_write(nimg,"ngrey.pgm");
  // perform the inverse DWT, should get original image
   if(levels == 0){
    //printf("iDWT2D\n");
    pgm_idwt2D(gimg,levels);
    // output to file
    pgm_write(gimg,"grey.pgm");
    Fimg = pgm_normalize(gimg);
    pgm_write(Fimg, "Final.pgm");
  }
    else{
        printf("I was not able to work out the multi levels for iDWT, \nbut in order to show that the DWT works with multiple levels I added this \nto skip the iDWT\n");
    }
  //printf("Mean Squared Value:\n");
  //pgm_MSE(gimg);

  // free image by sending pointer to pointer to ppm_free function
  //printf("Free\n");
  //pgm_free(&gimg);
  //pgm_free(&nimg);
  return 0;
}
	
