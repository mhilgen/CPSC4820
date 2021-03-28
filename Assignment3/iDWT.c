
void    pgm_idwt2D(PGM*img, int levels){
    FLTR *wimg = make_filter();
    int high = (log10(img->rows))/(log10(2.0));
    int low = high - levels;
    int r = 512; //img->rows;
    int c = 512; //img->cols;
    int i, j, m, jj, ii;
    int roff = r << 1;
    int coff = c << 1;
    int r2 = r << 1;
    int c2 = c << 1;
    PGM *Hr = pgm_alloc(r, c);
    PGM *Gr = pgm_alloc(r, c);
    PGM *rA = pgm_alloc(r2, c2);
    PGM *cA = pgm_alloc(r2, c2);
    
    for(int k = high; k >= low; k--){
        
        for(i = 0; i < r; i++){
            for(j = 0; j < c2; j++){
                ii = i << 1;
                rA->greypix[ii*r2+j] = img->greypix[i*c+j];
                rA->greypix[(ii+1)*r2+j] = img->greypix[(i+roff)*c+j];
                    //printf("\ti: %d, j: %d, m: %d\n", i, j, m);
            }
        }
        printf("\tPassed 1\n");
        for(i = 0; i < r; i++){
            for(j = 0; j < c; j++){
                ii = i << 1;
                for(m = 0; m < 18; m++){
                    Hr->greypix[ii*r+j] += wimg->ih[m] * rA->greypix[(ii+m)*r2+j];
                    Hr->greypix[(ii+1)*r+j] += wimg->ig[m] * rA->greypix[(ii+m)*r2+j];
                    Gr->greypix[ii*r+j] += wimg->ih[m] * rA->greypix[(ii+m)*r2+j];
                    Gr->greypix[(ii+1)*r+j] += wimg->ig[m] * rA->greypix[(ii+m)*r2+j];
                    //printf("\ti: %d, j: %d, m: %d\n", i, j, m);
                }
            }
        }
        printf("\tPassed 2\n");
        
        for(i = 0; i < r2; i++){
            for(j = 0; j < c; j++){
                jj = j << 1;
                    cA->greypix[i*c2+jj] = Hr->greypix[i*c+j];
                    cA->greypix[i*c2+(jj+1)] = Gr->greypix[i*c+(j+coff)];
                    //printf("\ti: %d, j: %d, m: %d\n", i, j, m);
            }
        }
        printf("\tPassed 3\n");
        //combining the Hr and Gr to the img
        for(i = 0; i < r; i++){
            for(j = 0; j < c; j++){
                jj = j << 1;
                 img->greypix[i*r+j] = 0.0;
                 img->greypix[(i+roff)*r+j] = 0.0;
                 img->greypix[i*r+(j+coff)] = 0.0;
                 img->greypix[(i+roff)*r+(j+coff)] = 0.0;
                for(m = 0; m < 18; m++){
                    img->greypix[i*r+(jj)] += wimg->ih[m] * cA->greypix[i*c2+j];
                    img->greypix[i*r+(jj+1)] += wimg->ig[m] * cA->greypix[i*c2+(j+1)];
                }
            }
        }
        //pgm_free(&rA);
        //pgm_free(&cA);
        printf("\tPassed 4\n");
        r2 = r2*2;
        c2 = c2*2;   
        coff = coff*2;
        roff = roff*2;
    }
    /*
    pgm_free(&rA);
    pgm_free(&cA);
    pgm_free(&Hr);
    pgm_free(&Gr);
    */
   printf("finish\n");
}
