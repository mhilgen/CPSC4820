
#include "pgm.h"
#include "Filter.h"

int main(int argc,char **argv)
{
        PGM      *gimg=NULL;
        PGM      *ndximg=NULL, *ndyimg=NULL;
        PGM      *dximg=NULL, *dyimg=NULL;
        FLTR     *gxp=make_filter(0), *gyp=make_filter(1);

  // allocte image of given size
  gimg = pgm_read("mandrill.pgm");

  // convolve
  dximg = pgm_conv(gimg,gxp);
  dyimg = pgm_conv(gimg,gyp);

  // copy edge image and normalize, for visualization purposes
  ndximg = pgm_normalize(dximg);
  pgm_write(ndximg,"ndxgrey.pgm");
  ndyimg = pgm_normalize(dyimg);
  pgm_write(ndyimg,"ndygrey.pgm");

  // output to file
  pgm_write(dximg,"dxgrey.pgm");
  pgm_write(dyimg,"dygrey.pgm");

  // free image by sending pointer to pointer to ppm_free function
  pgm_free(&dximg);
  pgm_free(&dyimg);
  pgm_free(&gimg);
  free_filter(&gxp);
  free_filter(&gyp);
  
  return 0;
}