
Name: Max Hilgenberg
Class: 4820 Section 3
Assignment 6
Date: 03/24/2021

The assignment was quite interesting to implement. I struggled first to find out that I needed a 10 x 7 Chessboard in order to have a 9x6 implementation in the Code.
This cost me a bit of time, while I figured it out just rewatching the lecture videos, which I should have done earlier.
I thought I could just use the data from the cv2.calibrateCamera function to get all the variables to draw the axis, but I needed to use the cv2.solvePnP function to
ensure that the axis goes with the Chessboard and not the frame itself.
The last difficult thing for me was to write all the camera matrix and distortion coefficients in two separate csv files without overwriting it. I tried several methods
until I finally figured out the right way and that I could str() any integer for the csv writer.
This was pretty fun to write even if it was a bit of a headache at the beginning.

Instructions:
    python Asg6.py