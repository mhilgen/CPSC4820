# Max Hilgenberg
# Final Project
# 04/14/2021
# Snapacht Filter Extended

import cv2
#method I used to put the layer / filter wanted on the original image
def filter(img, layer, x, y):
    #setting up the variables for each frame
    ih, iw = img.shape[:2]
    lh, lw = layer.shape[:2]
    # compares if the layer is greater than the original frame
    if x >= iw or y >= ih:
        return img
    #if the layer is less than the original frame
    if lw + x <= 0 or lh + y <= 0:
        return img
    # resizes the layer for x and y axis
    if x + lw > iw:
        lw =  iw - x
        layer = layer[:, :lw]
    if y + lh > ih:
        lh = ih - y
        layer = layer[:lh]

    #making it opaque
    if layer.shape[2] == 3:
        img[y:y+lh, x:x+lw] = layer
    #otherwise transparent
    else:
        mask = layer[..., 3:]/255.0
        img[y:y+lh, x:x+lw] = mask*layer[...,:3] + (1-mask) * img[y:y+lh, x:x+lw]
    return img
#triggers set up for each filter
mustache_button = False
beard_button = False
glasses_button = False
monocle_button = False
nose_button = False
face_button = False
eye_button = False
disguise_button = False
manchu_button = False
hat_button = False
cap_button = False

#paths of the video and the Haar xml files
imagePath = 'Max.mov'
facePath = "haarcascades/haarcascade_frontalface_alt2.xml"
leyePath = "haarcascades/haarcascade_lefteye_2splits.xml"
nosePath = "haarcascades/haarcascade_mcs_nose.xml"

#creating cascades for all facial features including the face
faceCascade = cv2.CascadeClassifier(facePath)
leyeCascade = cv2.CascadeClassifier(leyePath)
noseCascade = cv2.CascadeClassifier(nosePath)

#getting the video from the Directory
cap = cv2.VideoCapture(imagePath)
#setting up the video capture
width = int(cap.get(3))
height = int(cap.get(4))
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
fps = 20
out = cv2.VideoWriter('output.mp4', fourcc, fps, (width, height))
# when the video is run
while cap.isOpened():
    ret, frame = cap.read()
    if ret == True:
        #creates a text for the Instructions when running the program for the user to see what to press
        name = 'Instructions'
        font = cv2.FONT_HERSHEY_DUPLEX
        y0, dy, text = 30, 25, "Instructions: \nEnable/Disable Mustache = 'm' \nEnable/Disable Beard = 'b'\nEnable/Disable Manchu = 'J'\nEnable/Disable Glasses = 'g'\nEnable/Disable Disguise = 'd' \nEnable/Disable Monocle = 'e'\nEnable/Disable Gradcap = 'c'\nEnable/Disable Hat/Monocle/Beard = 'h'\nQuit Program = 'Q'"
        for i, line in enumerate(text.split('\n')):
            y = y0 + i * dy
            cv2.putText(frame, line, (10, y), font, .5, (0, 0, 0), 1, cv2.LINE_AA, False)
        cv2.imshow(name, frame)

        #make the fram grey for better results when finding the facial features
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        maxArea = 0
        x = 0
        y = 0
        h = 0
        w = 0
        #face
        faces = faceCascade.detectMultiScale(gray, 1.05, 5, minSize=(w // 6, h // 6))
        for fx, fy, fw, fh in faces:
            if fw * fh > maxArea:
                x = fx
                y = fy
                w = fw
                h = fh
                maxArea = w * h
            if maxArea > 0:
                # red rectangle that should have the face inside
                if face_button:
                    cv2.rectangle(frame, (x-20, y-20), (x + w + 20, y + h+20), (0, 0, 255), 2)

                w2 = fw // 2
                h2 = fh // 2
                x2 = fx + w2 // 2
                y2 = fy + h2 // 2
            # if any button that has to do with the nose is pressed this gets triggered
            if nose_button or mustache_button or beard_button or glasses_button or disguise_button or manchu_button or cap_button:
                grayroi = gray[y2:y2 + h2, x2:x2 + w2]
                noses = noseCascade.detectMultiScale(grayroi, minSize=(w // 6, h // 6))
                for nx, ny, nw, nh in noses:
                    # when the Manchu mustache gets triggered
                    if manchu_button:
                        # gets the image of the manchu from the filters directory
                        manchu = cv2.imread('filters/manchu.png', -1)
                        oh, ow = manchu.shape[:2]
                        scale = .85 * w / ow
                        layer = cv2.resize(manchu, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        #puts the manchu on the original image
                        frame = filter(frame, layer, xx, yy + 10)

                    # when the mustache is triggered
                    if mustache_button:
                        #gets the image of the mustache from the filters directory
                        mustache = cv2.imread('filters/mustache.png', -1)
                        oh, ow = mustache.shape[:2]
                        scale = .7 * w / ow
                        layer = cv2.resize(mustache, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        # puts the mustache on the original image
                        frame = filter(frame, layer, xx, yy + 3)
                    # puts the nose frame on the original image
                    if nose_button:
                        cv2.rectangle(frame, (x2 + nx, y2 + ny), (x2 + nx + nw, y2 + ny + nh), (0, 255, 0), 1)
                    # when the beard is triggered
                    if beard_button:
                        # gets the image of the beard from the filters director
                        beard = cv2.imread('filters/beard.png', -1)
                        oh, ow = beard.shape[:2]
                        scale = .85 * w / ow
                        layer = cv2.resize(beard, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        # puts the beard on the original image
                        frame = filter(frame, layer, xx, yy - 30)
                    # when the glasses are triggered
                    if glasses_button:
                        # gets the image of the glasses from the filters director
                        glasses = cv2.imread('filters/glasses.png', -1)
                        oh, ow = glasses.shape[:2]
                        scale = .85 * w / ow
                        layer = cv2.resize(glasses, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        # puts the glasses on the original images
                        frame = filter(frame, layer, xx, yy - 90)
                    # when the disguise is triggered
                    if disguise_button:
                        # gets the image of the disguise from the filters director
                        disguise = cv2.imread('filters/disguise.png', -1)
                        oh, ow = disguise.shape[:2]
                        scale =  w / ow
                        layer = cv2.resize(disguise, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        # puts the disguise on the original image
                        frame = filter(frame, layer, xx, yy - 150)

                    # when the cap is triggered
                    if cap_button:
                        # gets the image of the cap from the filters director
                        disguise = cv2.imread('filters/hat.png', -1)
                        oh, ow = disguise.shape[:2]
                        scale = 2 * w / ow
                        layer = cv2.resize(disguise, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + nx + (nw // 2) - (ow2 // 2)
                        yy = y2 + ny + (ny // 2) + (oh2 // 12)
                        # puts the cap on the original image
                        frame = filter(frame, layer, xx, yy - 335)

            # if anything that has to do with the left eye is triggered
            if monocle_button or eye_button or hat_button:
                #left eye
                w3 = fw // 2
                h3 = fh // 2
                x3 = fx + w3 // 4
                y3 = fy + h3 // 3
                grayroi = gray[y3:y3 + h3, x3:x3 + w3]
                leyes = leyeCascade.detectMultiScale(grayroi, minSize = (w // 10, h // 10))
                for lex, ley, lew, leh in leyes:
                    #draws the rectangle at the left eye
                    if eye_button:
                        cv2.rectangle(frame, (x3 + lex, y3 + ley), (x3 + lex + lew, y3 + ley + leh), (255, 0, 0), 1)
                    # when the monocle is triggered
                    if monocle_button:
                        # gets the image of the monocle from the filters director
                        monocle = cv2.imread('filters/monocle.png', -1)
                        oh, ow = monocle.shape[:2]
                        scale = .4 * w / ow
                        layer = cv2.resize(monocle, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x3 + lex + (lew // 2) - (ow2 // 2)
                        yy = y3 + ley + (ley // 2) + (oh2 // 12)
                        # puts the monocle on the original image
                        frame = filter(frame, layer, xx, yy - 10)
                    # when the hat is triggered
                    if hat_button:
                        # gets the image of the hat from the filters director
                        hat = cv2.imread('filters/hatcover.png', -1)
                        oh, ow = hat.shape[:2]
                        scale = 1.4 * w / ow
                        layer = cv2.resize(hat, (0, 0), fx=scale, fy=scale)
                        oh2, ow2 = layer.shape[:2]
                        xx = x2 + lex + (lew // 2) - (ow2 // 2)
                        yy = y2 + ley + (ley // 2) + (oh2 // 12)
                        # puts the hat on the original image
                        frame = filter(frame, layer, xx + 25, yy - 250)
        #shows the image while running the program so you can see what triggers to use
        cv2.imshow('Face Filter Window', frame)
        #writes the video out at the same time
        out.write(frame)
    else:
        break
    #needed triggers that are scanned on the keyboard when the user wants them to be true or false
    keyboard = cv2.waitKey(1) & 0xFF
    #stops the program
    if keyboard == ord('q'):
        break
    #otherwise it will trigger the triggers to be either true or false when pressed
    elif keyboard == ord('m'):
        mustache_button = not mustache_button
    elif keyboard == ord('b'):
        beard_button = not beard_button
    elif keyboard == ord('e'):
        monocle_button = not monocle_button
    elif keyboard == ord('n'):
        nose_button = not nose_button
    elif keyboard == ord('f'):
        face_button = not face_button
    elif keyboard == ord('g'):
        glasses_button = not glasses_button
    elif keyboard == ord('l'):
        eye_button = not eye_button
    elif keyboard == ord('d'):
        disguise_button = not disguise_button
    elif keyboard == ord('j'):
        manchu_button = not manchu_button
    elif keyboard == ord('h'):
        hat_button = not hat_button
    elif keyboard == ord('c'):
        cap_button = not cap_button

# When everything is done, release the capture
cap.release()
out.release()
cv2.destroyAllWindows()