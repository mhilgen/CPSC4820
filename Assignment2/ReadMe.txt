
Name: Max Hilgenberg
Class: 4820 Section 3
Assignment 2
Date: 01/25/2021

This program is making a greyimge (.pgm) two convoluted pictures, one with vertical edges, the other with horizontal edges. 
Then both images get normalized 
Then writen out. 

Problems I had:
In the beginning it was hard to find a good way to make the filter and normalizing the picture. 
I then figured out how to copy the images to make sure that normalization works.
After that I had a half way working program, which created the right horizontal image, but the vertical image didnt works.
So I only had half the images 2/4 correct. After extensive help from the Professor I was getting closer and closer 
to figure out how to use both the dy and dx filter for my convolution function.
This program taught me a lot, even though I could reuse some knowledge from Asg 1, I was still learning more and more on 
how convolution worked. I switched my i's and j's whihc resulted in messing up my convolution. 
Also my denom function was wrong, since I had maxc+minc+1, instead of maxc+minc. After fixing that it worked great and also works 
on the SoC.

Usage:
just use the make command and then the ./main 
the make clean command works as well and deletes all the images except the original.

Shortcut: 
make && ./main
