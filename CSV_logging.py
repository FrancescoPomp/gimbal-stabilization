import serial

#opening the correct serial port at the standardized baud rate
ser = serial.Serial('COM3', 115200, timeout=1)

ser.dtr = True
ser.dtr = False

#openign text file
with open("csv.csv","w", newline = '') as file:
    #writing header to the file for graphing reasons
    file.write("timestamp_ms,gyrox_dps,gyroy_dps,gyroz_dps,accelx_gs,accely_gs,accelz_gs\n")
    #decoding and writing everything that comes into the serial port until program is stopped
    while True:
        file.write(ser.readline().decode('utf-8'))