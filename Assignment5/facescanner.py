import cv2
#paths of the video and the Haar xml files
imagePath = 'angela.mp4'
facePath = "haarcascades/haarcascade_frontalface_alt2.xml"
reyePath = "haarcascades/haarcascade_righteye_2splits.xml"
leyePath = "haarcascades/haarcascade_lefteye_2splits.xml"
mouthPath = "haarcascades/haarcascade_smile.xml"
nosePath = "haarcascades/haarcascade_mcs_nose.xml"

#creating cascades for all facial features including the face
faceCascade = cv2.CascadeClassifier(facePath)
leyeCascade = cv2.CascadeClassifier(leyePath)
reyeCascade = cv2.CascadeClassifier(reyePath)
mouthCascade = cv2.CascadeClassifier(mouthPath)
noseCascade = cv2.CascadeClassifier(nosePath)

#getting the video from the Directory
cap = cv2.VideoCapture(imagePath)

width = int(cap.get(3))
height = int(cap.get(4))
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
fps = 30
out = cv2.VideoWriter('output.mp4', fourcc, fps, (width, height))
while cap.isOpened():
    ret, frame = cap.read()
    if ret == True:
        #make the fram grey for better results when finding the facial features
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        maxArea = 0
        x = 0
        y = 0
        h = 0
        w = 0
        #face
        faces = faceCascade.detectMultiScale(gray, 1.05, 5, minSize=(w // 6, h // 6))
        #red rectangle that should have the face inside
        for fx, fy, fw, fh in faces:
            if fw * fh > maxArea:
                x = fx
                y = fy
                w = fw
                h = fh
                maxArea = w * h
            if maxArea > 0:
                cv2.rectangle(frame, (x-20, y-20), (x + w + 20, y + h+20), (0, 0, 255), 2)
            #nose
            w2 = fw // 2
            h2 = fh // 2
            x2 = fx + w2 // 2
            y2 = fy + h2 // 2
            grayroi = gray[y2:y2 + h2, x2:x2 + w2]
            noses = noseCascade.detectMultiScale(grayroi, minSize=(w // 6, h // 6))
            for nx, ny, nw, nh in noses:
                cv2.rectangle(frame, (x2 + nx, y2 + ny), (x2 + nx + nw, y2 + ny + nh), (0, 255, 0), 1)

            #left eye
            w3 = fw // 2
            h3 = fh // 2
            x3 = fx + w3
            y3 = fy + h3 // 4
            grayroi = gray[y3:y3 + h3, x3:x3 + w3]
            leyes = leyeCascade.detectMultiScale(grayroi, minSize = (w // 10, h // 10))
            for lex, ley, lew, leh in leyes:
                cv2.rectangle(frame, (x3 + lex, y3 + ley), (x3 + lex + lew, y3 + ley + leh), (255, 0, 0), 1)

            #right eye
            w4 = fw // 2
            h4 = fh // 2
            x4 = fx + w4 // 4
            y4 = fy + h4 // 3
            grayroi = gray[y4:y4 + h4, x4:x4 + w4]
            reyes = reyeCascade.detectMultiScale(grayroi, minSize=(w // 10, h // 10))
            for rex, rey, rew, reh in reyes:
                cv2.rectangle(frame, (x4 + rex, y4 + rey), (x4 + rex + rew, y4 + rey + reh), (255, 255, 255), 1)

            #mouth
            w5 = fw // 2
            h5 = fh // 2
            x5 = fx + w5 // 2
            y5 = fy + h5
            grayroi = gray[y5:y5 + h5, x5:x5 + w5]
            mouth = mouthCascade.detectMultiScale(grayroi, minSize=(w // 10, h // 10))
            for mx, my, mw, mh in mouth:
                cv2.rectangle(frame, (x5 + mx, y5 + my), (x5 + mx + mw, y5 + my + mh), (0, 213, 255), 1)

        cv2.imshow('Face Detector', frame)
        out.write(frame)
    else:
        break

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
cap.release()
out.release()
cv2.destroyAllWindows()
