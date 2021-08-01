from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
import cv2

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands = 1, detectionCon = 0.7)
mySerial = SerialObject("COM12", 9600, 1)



while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)

    if lmList:
        bbox = bbox['bbox']
        
        # Find how many fingers are up
        fingers = detector.fingersUp()
        totalFingers = fingers.count(1)
        cv2.putText(img, f'Fingers:{totalFingers}', (bbox[0] + 200, bbox[1] - 30),
                    cv2.FONT_HERSHEY_PLAIN, 2, (220, 0, 0), 2)

        # Find Hand Type
        myHandType = detector.handType()
        cv2.putText(img, f'Hand:{myHandType}', (bbox[0], bbox[1] - 30),
                    cv2.FONT_HERSHEY_PLAIN, 2, (220, 0, 0), 2)
    
        # Send's Data To Arduino when connected (Write the arduino's Port on line 7 otherwise it will not work)
        fingers = detector.fingersUp()
        print(fingers)
        mySerial.sendData(fingers)
        # fingers gives an array [thumb, index, middle, ring, pinky]
        
    
    cv2.imshow("Image", img)
    key = cv2.waitKey(1)
    if key == ord('q'):
        break