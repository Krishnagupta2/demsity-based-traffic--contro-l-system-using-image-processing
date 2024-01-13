import sys
sys.path.append('C:\\Python311\\Lib\\site-packages') 
import serial
import time
import cv2

# Replace 'COMX' with your Arduino's serial port (e.g., 'COM3' on Windows)
arduino_port = 'COM3'
baud_rate = 9600

try:
    arduino = serial.Serial(arduino_port, baud_rate)
    arduino.flush()
except serial.SerialException:
    print(f"Failed to open {arduino_port}. Make sure the port is correct.")
    exit()

# Load your reference images for background subtraction
empty_road_image = cv2.imread('m.jpg')

# Initialize your camera (use the appropriate camera index or file path)
camera = cv2.VideoCapture(1)

while True:
    # Capture an image from the camera
    ret, image = camera.read()

    if not ret:
        print("Failed to capture an image.")
        continue

    # Perform background subtraction to detect moving objects (e.g., cars)
    diff = cv2.absdiff(empty_road_image, image)
    gray = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)
    _, thresh = cv2.threshold(gray, 30, 255, cv2.THRESH_BINARY)

    # Find contours of moving objects (contours may represent cars)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Calculate the density of vehicles based on the area occupied by contours
    total_area = sum(cv2.contourArea(contour) for contour in contours)
    image_area = image.shape[0] * image.shape[1]
    density = total_area / image_area

    # Calculate the delay based on the density (adjust as needed)
    if density < 0.1:
        green_delay = 1000  # Low density
    elif 0.1 <= density < 0.5:
        green_delay = 3000  # Medium density
    
    else:
        green_delay = 5000  # High density

    # Send the delay to Arduino
    arduino.write(f"{green_delay}\n".encode())

    # Print the delay and wait for a moment before capturing the next frame
    print(f"Sent a delay of {green_delay} ms to the Arduino based on density: {density*100:.2f}")
    time.sleep(15 )  # Adjust the sleep duration as needed

# Release the camera and close the Arduino serial connection
camera.release()
arduino.close()