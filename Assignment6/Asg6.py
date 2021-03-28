import cv2
import numpy as np
import csv
import os

# Dimensions of the Chessboard if it needs to be changed
Chessboard = (6, 9)
framenumber = 0
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
objpoints = []
imgpoints = []
objectp = np.zeros((1, Chessboard[0] * Chessboard[1], 3), np.float32)
objectp[0, :, :2] = np.mgrid[0:Chessboard[0], 0:Chessboard[1]].T.reshape(-1, 2)

#paths of the video and the Haar xml files
imagePath = 'Chess.mov'
#getting the video from the Directory
cap = cv2.VideoCapture(imagePath)
#needed for writing the output file
width = int(cap.get(3))
height = int(cap.get(4))
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
fps = 20
out = cv2.VideoWriter('output.mp4', fourcc, fps, (width, height))

while cap.isOpened():
    # reads the frames and turns it into a gray image
    retval, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # finds the chessboard of the frame
    ret, corners = cv2.findChessboardCorners(gray, Chessboard, cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_FAST_CHECK + cv2.CALIB_CB_NORMALIZE_IMAGE)

    if ret == True:
        objpoints.append(objectp)
        corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
        imgpoints.append(corners2)
        # Draw and display the corners
        img = cv2.drawChessboardCorners(img, (9, 6), corners2, ret)
        # finds the camera matrix and distortion coefficients of the board
        ret, mtrx, dist, rvec, tvec = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
        # finds the rvecs and tvecs
        retPnP, rvecs, tvecs = cv2.solvePnP(objectp, corners2, mtrx, dist)
        rvecs = rvecs.T
        tvecs = tvecs.T
        # draws the x, y and z axis on the board while the z axis goes inward the page which makes it less accurate
        img = cv2.drawFrameAxes(img, mtrx, dist, rvecs[0], tvecs[0], 8)
        cv2.imshow("Axis", img)
        out.write(img)
        # prints the matrix and distortion coefficients with telling which Frame it is from
        framer = "Frame " + str(framenumber) + ":"
        print(framer)
        print("Matrix : ")
        print(mtrx)
        print("\ndist : ")
        print(dist)

        #saves the same information from the print statemetns to two csv files
        np.savetxt('matrix.csv', mtrx, delimiter=',')
        np.savetxt('dist.csv', dist, delimiter=',')

        framenumber = framenumber + 1
    else:
        break

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# When everything is done, release the capture
cap.release()
out.release()
cv2.destroyAllWindows()

