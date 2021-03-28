
#include "Filter.h"
//frees the variables of the filter 
void free_filter(FLTR **img){
    
    if((*img)->dx){
        free((*img)->dx);
    }
    if((*img)->dy){
        free((*img)->dy);
    }
}
//filter for the dy and dx
FLTR *make_filter(int num){
    //declaring and allocating memory for image 
    FLTR *gimg= NULL;
    gimg = (FLTR *)malloc(sizeof(FLTR));
    gimg->dx = (float *)malloc(3*sizeof(float));
    gimg->dy = (float *)malloc(3*sizeof(float));
    //making sure to get the right dx and dy for the vertical and horizontal filter
    //they basically switch 
    if(num == 1){
        gimg->dx[0] = 1;
        gimg->dx[1] = 0;
        gimg->dx[2] = -1;
    
        gimg->dy[0] = 1;
        gimg->dy[1] = 2;
        gimg->dy[2] = 1;
    }
    if(num == 0){
        gimg->dx[0] = 1;
        gimg->dx[1] = 2;
        gimg->dx[2] = 1;
        
        gimg->dy[0] = 1;
        gimg->dy[1] = 0;
        gimg->dy[2] = -1;
    }
    return gimg;
}
