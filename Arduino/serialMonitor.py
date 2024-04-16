import serial
import time

# Open the serial port (replace '/dev/ttyACM0' with your port)
ser = serial.Serial('COM5', 9600)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
    time.sleep(0.05)