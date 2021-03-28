import cv2
import numpy as np

#Captures the video input from input.mp4
#path = 'landscape.mp4' I was just playing around with images here to see how it works
path = 'fractal.mp4'
#path = 'mandrill.mp4' just wanted to see how the mandrill would actaully look moving 
cap = cv2.VideoCapture(path)
#couldnt get the size variable to work so I looked it up how to get width and height 
width = int(cap.get(3))
height = int(cap.get(4))
#getting the right converter for the output file 
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
fps = 30
# sets up the out to be in the right format 
out = cv2.VideoWriter('output.mov', fourcc, fps, (width, height))
#hsvout = cv2.VideoWriter('HSV_output.mov', fourcc, fps, (width, height))

while(cap.isOpened()):
  ret, frame = cap.read()
  #makes the video grey per frame which I thought was cool with a fractal
  #hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
  #grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  if ret == False:
      break
  if ret == True: 
    #shows the greyscale image
    #cv2.imshow('HSV',hsv)
      #creates the video frame by frame colored though not grey since I could not get it to work
    out.write(frame)
    #creates a differnt color type of video which I thought looked cool with fractals 
    #lsdout.write(lsd)
    
    #in case you want to exit during the imshow
    if cv2.waitKey(1) & 0xFF == ord('q'):
      break

  # Break the loop
  else:
    break  
#closes everything when the conversion is done
cap.release()
out.release()
# Closes all the windows 
cv2.destroyAllWindows() 
