import serial
import time
import pymongo

# Configure the serial port
# Replace 'COMx' with your actual serial port (e.g., 'COM3' on Windows, '/dev/ttyUSB0' on Linux)
# Set the baud rate to match your device (e.g., 9600, 115200)
ser = serial.Serial(
    port="COM6",  # Change this to your serial port
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1,  # Timeout in seconds (important for non-blocking reads)
)

print(f"Connected to: {ser.portstr}")
myclient = pymongo.MongoClient("mongodb://localhost:27017/")

mydb = myclient["sonar_dis"]
mycol = mydb["a"]
try:
    while True:
        # Read a line of data until a newline character ('\n') is encountered
        # .readline() returns bytes, so decode it to a string
        line = ser.readline().decode("utf-8").strip()
        if line:  # Only print if data was received
            print(f"Received: {line}")
            x = mycol.insert_one({"valve": line})

            print(x.inserted_id)
        time.sleep(0.1)  # Small delay to prevent busy-waiting
except KeyboardInterrupt:
    print("Exiting program.")
finally:
    ser.close()
    print("Serial port closed.")
