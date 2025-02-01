import serial
import time
import requests

# Replace with your Arduino's port and correct API endpoint
arduino_port = "COM6"  # Update with your actual Arduino port
baud_rate = 9600  # Match the baud rate in Arduino code
api_url = "http://jpcanamaque:8000/final_lab?"  # Base API endpoint
group_name = "group4_on"  # Replace with your group name if needed

# Establish serial connection
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)  # Wait for the connection to initialize
    print("Serial connection established. Waiting for button presses...")
except Exception as e:
    print(f"Error: Could not open serial port. Details: {e}")
    exit()

# Function to send HTTP requests to the API
def send_api_request(state):
    endpoint = f"{api_url}?groupName={group_name}"
    payload = {"button_state": state}
    try:
        response = requests.post(endpoint, json=payload, timeout=5)  # 5-second timeout
        if response.status_code == 200:
            print(f"API called successfully! State: {state}")
        else:
            print(f"API call failed. Status code: {response.status_code}, Response: {response.text}")
    except requests.exceptions.RequestException as e:
        print(f"Error during API call: {e}")

# Main loop to read data and interact with the API
try:
    while True:
        if ser.in_waiting > 0:  # Check if data is available
            data = ser.readline().decode('utf-8').strip()  # Read and decode data
            print(f"Received data: {data}")

            if data == "group4_on":  # Button pressed
                print("Button Pressed")
                send_api_request("on")  # Call the API for LED ON
            elif data == "group4_off":  # Button released
                print("Button Not Pressed")
                send_api_request("off")  # Call the API for LED OFF
            else:
                print("Unexpected data received.")

except KeyboardInterrupt:
    print("\nExiting...")

finally:
    ser.close()  # Close the serial connection
    print("Serial connection closed.")
