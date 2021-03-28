
#include "Filter.h"
//frees the variables of the filter 
void free_filter(FLTR **img){
    
    if((*img)->g){
        free((*img)->g);
    }
    if((*img)->h){
        free((*img)->h);
    }
    if((*img)->ig){
        free((*img)->ig);
    }
    if((*img)->ih){
        free((*img)->ih);
    }
}
//filter for the dy and dx
FLTR *make_filter(){
    //declaring and allocating memory for image 
    FLTR *wimg= NULL;
    wimg = (FLTR *)malloc(sizeof(FLTR));
    wimg->g = (float *)malloc(18*sizeof(float));
    wimg->h = (float *)malloc(18*sizeof(float));
    wimg->ih = (float *)malloc(18*sizeof(float));
    wimg->ig = (float *)malloc(18*sizeof(float));
    
    //low wavelet
        wimg->h[0] = 0;
        wimg->h[1] =  0.0015105431;
        wimg->h[2] = -0.0030210861;
        wimg->h[3] = -0.0129475119;
        wimg->h[4] =  0.0289161098;
        wimg->h[5] =  0.0529984819;
        wimg->h[6] = -0.1349130736;
        wimg->h[7] = -0.1638291834;
        wimg->h[8] =  0.4625714405;
        wimg->h[9] =  0.9516421219;
        wimg->h[10] =  0.4625714405;
        wimg->h[11] = -0.1638291834;
        wimg->h[12] = -0.1349130736;
        wimg->h[13] =  0.0529984819;
        wimg->h[14] =  0.0289161098;
        wimg->h[15] = -0.0129475119;
        wimg->h[16] = -0.0030210861;
        wimg->h[17] =  0.0015105431;
    //high wavelet
        wimg->g[0] = 0;
        wimg->g[1] = 0;
        wimg->g[2] = 0;
        wimg->g[3] = 0;
        wimg->g[4] = 0;
        wimg->g[5] = 0;
        wimg->g[6] = 0;
        wimg->g[7] =  0.3535533906;
        wimg->g[8] = -0.7071067812;
        wimg->g[9] =  0.3535533906;
        wimg->g[10] = 0;
        wimg->g[11] = 0;
        wimg->g[12] = 0;
        wimg->g[13] = 0;
        wimg->g[14] = 0;
        wimg->g[15] = 0;
        wimg->g[16] = 0;
        wimg->g[17] = 0;
    // inverse low wavelet
        wimg->ih[0] = 0;
        wimg->ih[1] = 0;
        wimg->ih[2] = 0;
        wimg->ih[3] = 0;
        wimg->ih[4] = 0;
        wimg->ih[5] = 0;
        wimg->ih[6] = 0;
        wimg->ih[7] =  0.3535533906;
        wimg->ih[8] =  0.7071067812;
        wimg->ih[9] =  0.3535533906;
        wimg->ih[10] = 0;
        wimg->ih[11] = 0;
        wimg->ih[12] = 0;
        wimg->ih[13] = 0;
        wimg->ih[14] = 0;
        wimg->ih[15] = 0;
        wimg->ih[16] = 0;
        wimg->ih[17] = 0;
    //inverse high wavelet 
        wimg->ig[0] = 0;
        wimg->ig[1] = -0.0015105431;
        wimg->ig[2] = -0.0030210861;
        wimg->ig[3] =  0.0129475119;
        wimg->ig[4] =  0.0289161098;
        wimg->ig[5] = -0.0529984819;
        wimg->ig[6] = -0.1349130736;
        wimg->ig[7] =  0.1638291834;
        wimg->ig[8] =  0.4625714405;
        wimg->ig[9] = -0.9516421219;
        wimg->ig[10] =  0.4625714405;
        wimg->ig[11] =  0.1638291834;
        wimg->ig[12] = -0.1349130736;
        wimg->ig[13] = -0.0529984819;
        wimg->ig[14] =  0.0289161098;
        wimg->ig[15] =  0.0129475119;
        wimg->ig[16] = -0.0030210861;
        wimg->ig[17] = -0.0015105431;
    return wimg;
}
