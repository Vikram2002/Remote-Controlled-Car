import serial
import os
arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout = 0.1)

os.system("x-terminal-emulator -e python3 capture.py")
os.system("x-terminal-emulator -e python3 Website/server.py")

cache = ""

while True:
    f = open("Instructions.txt", "r")
    instructions = f.readlines()
    f.close();

    data = ""
    if len(instructions) > 0:
        data = instructions[0]

    if cache == data:
        continue;

    print(data)

    if data == "Moving Forward":
        arduino.write(bytes('0', "utf-8"))

    if data == "Moving Backward":
        arduino.write(bytes('1', "utf-8"))

    if data == "Turning Right":
        arduino.write(bytes('2', "utf-8"))

    if data == "Turning Left":
        arduino.write(bytes('3', "utf-8"))

    if data == "Camera Left":
        arduino.write(bytes('5', "utf-8"))

    if data == "Camera Right":
        arduino.write(bytes('6', "utf-8"))

    if data == "Camera Up":
        arduino.write(bytes('7', "utf-8"))

    if data == "Camera Down":
        arduino.write(bytes('8', "utf-8"))

    if data == "Idle":
        arduino.write(bytes('4', "utf-8"))

    cache = data
