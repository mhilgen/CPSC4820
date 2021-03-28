
Name: Max Hilgenberg
Class: 4820 Section 3
Assignment 3
Date: 02/18/2021

This assignment was meant to introduce us how to use OpenCV. 
It helped me to get started and understand how to read, copy and perhaps also change a color video. 
I played around a bit with the Color Cnversion Codes and found some cool ones. Since I used a fractal video, 
I thought it would look really cool if I would have the original outputted, then show the greyscale version of it 
using imgshow and then make another video output as the LSD version where the colors are HSV converted.
It definetly was a lot of fun to play around with a video instead of the previous assignment. 
I did play around with some other videos like the landscape or the mandrill itself just to go back to the basics
I commented out my second output file since it created a warning that I could not fix. but it does work and create a second 
output file without any issues. I just did not want to loose points for doing something else in this assignment. 
I also added a pdf file to the directory to just show some other videos and conversions I did with the input files. For some reason it does 
not make the gifs move for some reason and I did not want to add a 100 MB ppt.  I had to disable the color
conversions in the python file itself since it kept throwing me a warning at the end of the runtime for the cvtColor function, even though it 
ran through the whole time. 

Instructions:
For me the ./videocopy.py does not work on SoC so I do not know if it will work for you. Even after using the chmod u+x videocopy.py command
Howeverm python videocopy.py works for me perfectly. There should be no need for input.
Command:
    python videocopy.py
