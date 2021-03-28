
Name: Max Hilgenberg
Class: 4820 Section 3
Assignment 1
Date: 01/12/2021

This assignment was an introduction to show us how to manipulate images.
We read in the color image (.ppm) and converting it to a greyscale image (.pgm)
In order to not mess up the formatting we will read in the .ppm image and safe all the 
r g b values in seperate 1D arrays making sure they all line up correctly with the height 
and width of the image. Then we run the white scale function which uses this equation: 
0.21 R + 0.72 G + 0.07 B in order to greyscale the pixels 
After that we will add the r g b to x which is my greyscale pixels 
These will be then written into the pgm_write function to complete the .pgm header and pixel table 
After that the image will be created and the mandrill.ppm will be greyscaled into grey.ppm

I have learned a lot about image manipulation and how important each step to read the header 
is in order to get to the pixel tbale without formatting issues 
This assignment and the example given in class has given me a much better understanding on how 
to manipulate images, I will for sure use this basic knowledge for any future assignments 
The hardest part of this assignment for me was to get the greyscaling function to work with the PGM and PPM 
headers since the code was in ppm.c but still needed access to pgm.h in order to send the 
grey pixels to the right grey image 

Instructions:
just use the make command and then the ./main command to run the program 
Here is it in short and fast: 
    make && ./main 




