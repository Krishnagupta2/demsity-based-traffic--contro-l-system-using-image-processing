# Density-Based Traffic Control System using Image Processing

## Project Description
This project, titled "Density-Based Traffic Control System using Image Processing," aims to regulate traffic flow intelligently by analyzing vehicle density through image processing. The system captures real-time images of a road, processes them to identify moving objects (vehicles), and adjusts traffic signal timings based on the density of vehicles in the scene.

## Components
- **Python Script (density_control.py):**
  - Captures video feed from a camera (webcam or other source).
  - Utilizes background subtraction to identify moving objects.
  - Calculates vehicle density based on the area occupied by contours.
  - Sends delay information to the Arduino based on density.
  
- **Arduino Code (traffic_light_controller.ino):**
  - Controls a set of traffic lights with red, yellow, and green signals for two lanes.
  - Receives delay information from the Python script through serial communication.
  - Implements a countdown mechanism for red, yellow, and green signals.
  - Displays real-time information on an LCD screen.

## Requirements
- **Hardware:**
  - Arduino Board
  - Webcam or Camera Module
  - Two sets of LEDs (Red, Yellow, Green for each lane)
  - LCD Display (compatible with LiquidCrystal_I2C library)
  
- **Software:**
  - Python 3.x
  - OpenCV library for Python
  - Arduino IDE
  - Arduino LiquidCrystal_I2C library
  
## Setup Instructions

### Python Script
1. Install Python (https://www.python.org/) and required libraries:
   ```
   pip install opencv-python
   ```

2. Adjust the script parameters:
   - Set the correct Arduino serial port (`arduino_port`) in the Python script.
   - Update the file path for the reference empty road image (`empty_road_image`).
   - Modify camera index or file path based on your setup (`camera = cv2.VideoCapture(1)`).

3. Run the Python script:
   ```
   python density_control.py
   ```

### Arduino Code
1. Install Arduino IDE (https://www.arduino.cc/en/software) and open the Arduino code file (traffic_light_controller.ino).

2. Set up the Arduino board type and port in the Arduino IDE.

3. Upload the code to the Arduino board.

4. Connect the hardware components according to the pin configurations in the Arduino code.

## Project Execution
1. Run the Python script to capture and process the real-time video feed.
2. The script calculates vehicle density and adjusts the delay based on the traffic conditions.
3. The delay information is sent to the Arduino over serial communication.
4. The Arduino controls the traffic lights for two lanes, adapting signal timings according to the received delay.
5. The LCD display provides real-time information on the status of each lane and the countdown.

## Notes
- Adjust the delay thresholds in the Python script based on the specific traffic conditions in your application.
- Ensure proper connections between the Arduino and hardware components.
- Customize the LCD display messages or additional features based on project requirements.

Feel free to explore and enhance the project for more advanced features and applications. For any issues or inquiries, refer to the documentation or contact the project contributors.
