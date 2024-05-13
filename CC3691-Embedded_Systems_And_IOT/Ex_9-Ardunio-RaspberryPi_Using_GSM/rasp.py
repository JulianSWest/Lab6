import serial
import time
ser = serial.Serial('/dev/ttyS0', 9600) # Open serial port (replace '/dev/ttyS0' with appropriate
serial port)
ser.flushInput()
while True:
	if ser.in_waiting > 0:
		data = ser.readline().decode().strip() # Read data from serialprint("Received:", data)
	time.sleep(0.1)
