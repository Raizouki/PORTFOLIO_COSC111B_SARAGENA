import serial
import time
import requests

# Replace with your Arduino's port
arduino_port = "COM6"  # Example: "/dev/ttyUSB0" for Linux/Mac
baud_rate = 9600  # Match the baud rate in Arduino code

# API Endpoint
api_url = "http://192.168.110.198:8000"  # Replace with your API endpoint

# Establish serial connection
ser = serial.Serial("COM6", 9600)
time.sleep(2)  # Wait for the connection to initialize
print("Connection established. Waiting for button clicks...")

try:
    while True:
        if ser.in_waiting > 0:  # Check if data is available
            data = ser.readline().decode('utf-8').strip()  # Read and decode data

            if data == "1":  # Button pressed
                print("Button Pressed")
                # Call the API
                response = requests.post(api_url + '/led/on', json={"button_state": "pressed"})
                if response.status_code == 200:
                    print("API called successfully!")
                else:
                    print(f"API call failed with status code: {response.status_code}")

            elif data == "0":  # Button released
                print("Button Not Pressed")
                response = requests.post(api_url + '/led/off', json={"button_state": "pressed"})
                if response.status_code == 200:
                    print("API called successfully!")
                else:
                    print(f"API call failed with status code: {response.status_code}")

except KeyboardInterrupt:
    print("\nExiting...")

finally:
    ser.close()  # Close the serial connection