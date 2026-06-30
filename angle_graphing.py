import pandas as pd
import matplotlib.pyplot as plt



#Reading and adjusting timestamp of Bump1
bump1Data = pd.read_csv("Bump1.csv")
bump1Data.timestamp_ms = bump1Data.timestamp_ms - bump1Data.timestamp_ms[0]

#plotting Bump1 data for only X gyro angle, X accel angle, and X complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Bump Test 1 - X Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(bump1Data.timestamp_ms, bump1Data.gyrox_deg, label = "Gyroscope")
plt.plot(bump1Data.timestamp_ms, bump1Data.accelx_deg, label = "Accelerometer")
plt.plot(bump1Data.timestamp_ms, bump1Data.compfilterx_deg, label = "Complimentary Filter")
plt.plot(bump1Data.timestamp_ms, bump1Data.kalmanx_deg, label = "Kalman Filter")
plt.legend()
plt.savefig("Bump1XPlot.png")
plt.show()

#plotting Bump1 data for only Y gyro angle, Y accel angle, and Y complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Bump Test 1 - Y Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(bump1Data.timestamp_ms, bump1Data.gyroy_deg, label = "Gyroscope")
plt.plot(bump1Data.timestamp_ms, bump1Data.accely_deg, label = "Accelerometer")
plt.plot(bump1Data.timestamp_ms, bump1Data.compfiltery_deg, label = "Complimentary Filter")
plt.plot(bump1Data.timestamp_ms, bump1Data.kalmany_deg, label = "Kalman FIlter")
plt.legend()
plt.savefig("Bump1YPlot.png")
plt.show()



#Reading and adjusting timestamp of Bump2
bump2Data = pd.read_csv("Bump2.csv")
bump2Data.timestamp_ms = bump2Data.timestamp_ms - bump2Data.timestamp_ms[0]

#plotting Bump2 data for only X gyro angle, X accel angle, and X complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Bump Test 2 - X Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(bump2Data.timestamp_ms, bump2Data.gyrox_deg, label = "Gyroscope")
plt.plot(bump2Data.timestamp_ms, bump2Data.accelx_deg, label = "Accelerometer")
plt.plot(bump2Data.timestamp_ms, bump2Data.compfilterx_deg, label = "Complimentary Filter")
plt.plot(bump2Data.timestamp_ms, bump2Data.kalmanx_deg, label = "Kalman Filter")
plt.legend()
plt.savefig("Bump2XPlot.png")
plt.show()

#plotting Bump1 data for only Y gyro angle, Y accel angle, and Y complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Bump Test 2 - Y Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(bump2Data.timestamp_ms, bump2Data.gyroy_deg, label = "Gyroscope")
plt.plot(bump2Data.timestamp_ms, bump2Data.accely_deg, label = "Accelerometer")
plt.plot(bump2Data.timestamp_ms, bump2Data.compfiltery_deg, label = "Complimentary Filter")
plt.plot(bump2Data.timestamp_ms, bump2Data.kalmany_deg, label = "Kalman Filter")
plt.legend()
plt.savefig("Bump2YPlot.png")
plt.show()



#Reading and adjusting timestamp of StaticHold
staticData = pd.read_csv("StaticHold.csv")
staticData.timestamp_ms = staticData.timestamp_ms - staticData.timestamp_ms[0]

#plotting Static Hold data for only X gyro angle, X accel angle, and X complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Static Hold Test - X Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(staticData.timestamp_ms, staticData.gyrox_deg, label = "Gyroscope")
plt.plot(staticData.timestamp_ms, staticData.accelx_deg, label = "Accelerometer")
plt.plot(staticData.timestamp_ms, staticData.compfilterx_deg, label = "Complimentary Filter")
plt.plot(staticData.timestamp_ms, staticData.kalmanx_deg, label = "Kalman Filter")
plt.legend()
plt.savefig("StaticXPlot.png")
plt.show()

#plotting Static Hold data for only Y gyro angle, Y accel angle, and Y complimentary filter angle
plt.figure()
plt.title("Rotation Calculations with Different Methods - Static Hold Test - Y Rotation")
plt.xlabel("Timestamp (ms)")
plt.axhline(y=0, color = 'black')
plt.ylabel("Calculated Angle (deg)")
plt.plot(staticData.timestamp_ms, staticData.gyroy_deg, label = "Gyroscope")
plt.plot(staticData.timestamp_ms, staticData.accely_deg, label = "Accelerometer")
plt.plot(staticData.timestamp_ms, staticData.compfiltery_deg, label = "Complimentary Filter")
plt.plot(staticData.timestamp_ms, staticData.kalmany_deg, label = "Kalman Filter")
plt.legend()
plt.savefig("StaticYPlot.png")
plt.show()