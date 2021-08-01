from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
import cv2

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands = 1, detectionCon = 0.7)
mySerial = SerialObject("COM12", 9600, 1)


while True:
    success, video = cap.read()
    video = detector.findHands(video)
    lmList, bbox = detector.findPosition(video)
    
    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
        mySerial.sendData(fingers)
        # fingers gives an array [thumb, index, middle, ring, pinky]
    
    cv2.imshow("Image", video)
    key = cv2.waitKey(1)
    if key == ord('q'):
        break