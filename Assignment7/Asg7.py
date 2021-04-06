import cv2
import numpy as np
import csv
import os

#paths of the video and the Haar xml files
imagePath = 'Aruco.mov'
#getting the video from the Directory
cap = cv2.VideoCapture(imagePath)
#needed for writing the output file
width = int(cap.get(3))
height = int(cap.get(4))
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
fps = 30
out = cv2.VideoWriter('output.mp4', fourcc, fps, (width, height))

length = 75
verts = np.float32([[length, 0, 0], [0, length, 0], [0, 0, length]]).reshape(-1, 3) 
cameraMatrix = np.loadtxt('matrix.csv', delimiter=",")
distCoeff = np.loadtxt('dist.csv', delimiter=",")

while cap.isOpened():
    # reads the frames and turns it into a gray image
    retval, img = cap.read()
    if retval == True:
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # finds the chessboard of the frame
        aruco_dict = cv2.aruco_Dictionary.get(cv2.aruco.DICT_4X4_1000)
        param = cv2.aruco_DetectorParameters.create()
        corners, ids, rejected = cv2.aruco.detectMarkers(gray, aruco_dict, parameters=param)
        cv2.aruco.drawDetectedMarkers(img, corners, ids,)
        rvecs, tvecs, _objPoints = cv2.aruco.estimatePoseSingleMarkers(corners, 0.15, cameraMatrix, distCoeff)
        #gets the origin point of the top left corner of the aruco marker
        origin = tuple(corners[0].ravel())
        cv2.aruco.drawAxis(img, cameraMatrix, distCoeff, rvecs, tvecs, 0.1)

        img =  cv2.line(img, (int(origin[0]), int(origin[1])), (int(origin[2]), int(origin[3])), (0, 255, 255), 2)
        img =  cv2.line(img, (int(origin[2]), int(origin[3])), (int(origin[4]), int(origin[5])), (0, 255, 255), 2)
        img =  cv2.line(img, (int(origin[4]), int(origin[5])), (int(origin[6]), int(origin[7])), (0, 255, 255), 2)
        img =  cv2.line(img, (int(origin[6]), int(origin[7])), (int(origin[0]), int(origin[1])), (0, 255, 255), 2)


        #draws the lines for the virtual rectanle
        #cv2.rectangle(img, (int(origin[0]), int(origin[1])), (int(origin[4]), int(origin[5])), (0, 255, 255), 2)
        #from the top right and top left
        img =  cv2.line(img, (int(origin[0]), int(origin[1])), (int(origin[0]-300), int(origin[1])), (255, 255, 0), 3)
        #from top left to bottom left
        img = cv2.line(img, (int(origin[0]-300), int(origin[1])), (int(origin[0] - 300), int(origin[1] + 200)), (255, 255, 0), 3)
        #from bottom right to top right
        img = cv2.line(img, (int(origin[0]), int(origin[1]+200)), (int(origin[0]), int(origin[1])), (255, 255, 0), 3)
        #from bottom left to bottom right
        img = cv2.line(img, (int(origin[0]-300), int(origin[1]+200)), (int(origin[0]), int(origin[1]+200)), (255, 255, 0), 3)

        cv2.imshow('Aruco', img)
        out.write(img)
    else:
        print("Done\n")
        break
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# When everything is done, release the capture
cap.release()
out.release()
cv2.destroyAllWindows()

