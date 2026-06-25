import serial

#inputting what test we would like to do so that the file is not overwritten for differnt tests
while True:
    fileName = input("Specify Test(StaticHold, Bump1, Bump2): ")
    if (fileName == "StaticHold" or fileName == "Bump1" or fileName == "Bump2"):
        break
    else:
        print("Be specific with test name and choose one of the three options!")

input("Reset the Teensy 4.0 now. Click enter when finished.")

#opening the correct serial port at the standardized baud rate
ser = serial.Serial('COM3', 115200, timeout=1)

#openign text file
with open(fileName + ".csv","w", newline = '') as file:
    #writing header to the file for graphing reasons
    file.write("timestamp_ms,gyrox_deg,gyroy_deg,gyroz_deg,accelx_deg,accely_deg,compfilterx_deg,compfiltery_deg\n")
    #decoding and writing everything that comes into the serial port until program is stopped
    while True:
        file.write(ser.readline().decode('utf-8'))