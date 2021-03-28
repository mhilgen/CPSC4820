
Name: Max Hilgenberg
Class: 4820 Section 3
Assignment 3
Date: 02/16/2021

This assignment is build to show how Discrete wavelet transformation works. 
First we do a regular transformation with x amounts of levels. Then the image will be normalized. 
After that is done we use the unnormalized image and reconstruct the original image. 
I had a hard time to figure out the iDWT. As you will see I have not worked it out but got fairly close for level 0. 
However, after attempting to do it the way as it was supposed to be, I encountered seg faults all the time, which made my code not work at all. 
I have attached a iDWT.c file to show what my function would have looked like if I could have found the seg faults. It works sometimes but then creates a 
black image. I just wanted to attach that file to show that I was working on the iDWT another way, probably the right way.
 I think I was fairly close but I believe that I went over the maximum of my borders for rA and cA, which resulted in the seg faults, but the indexes looked fine to me, 
which was really frustrating since I could not find my errors. 
At least I hope that I can get partial credit for the DWT working completley for any level. Also the iDWT works almost perfect for level 0 with the code that I used for the pgm.c.
I was going to add the MSE function as seen in the main.c and pgm.c, however, I focused my time to try to get the iDWT to work which was unsuccessful as mentioned earlier.  

Instructions:
just use the make command and then the ./main command to run the program and the levels as much as you want.
Here is it in short and fast: 
    make && ./main (number of levels, starting at 0)