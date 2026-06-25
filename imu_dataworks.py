import pandas as pd
import matplotlib.pyplot as plt

ImuData = pd.read_csv("csv.csv")
ImuData.timestamp_ms = ImuData.timestamp_ms - ImuData.timestamp_ms[0]

#Plot Gyro data
plt.figure()
plt.xlabel("Timestamp (ms)")
plt.ylabel("Gyro (deg/s)")
plt.plot(ImuData.timestamp_ms, ImuData.gyrox_dps, label = "X")
plt.plot(ImuData.timestamp_ms, ImuData.gyroy_dps, label = "Y")
plt.plot(ImuData.timestamp_ms, ImuData.gyroz_dps, label = "Z")
plt.legend()
plt.title("Resting Gyroscope Analysis")
plt.savefig("gyro_noise_floor.png")
plt.show()

#plotting accel data
plt.figure()
plt.xlabel("Timestamp (ms)")
plt.ylabel("Accel (g's)")
plt.plot(ImuData.timestamp_ms, ImuData.accelx_gs, label = "X")
plt.plot(ImuData.timestamp_ms, ImuData.accely_gs, label = "Y")
plt.plot(ImuData.timestamp_ms, ImuData.accelz_gs, label = "Z")
plt.legend()
plt.title("Resting Accelerometer Analysis")
plt.savefig("accel_noise_floor.png")
plt.show()

#X angle error accumulation and dataframing the drift
XAngleError = 0.0
XDriftData = [[0.0, 0.0]] * ImuData.gyrox_dps.count()
for i in range(1, ImuData.gyrox_dps.count()):
    XAngleError = XAngleError + ((ImuData.gyrox_dps[i]/1000)*(ImuData.timestamp_ms[i] - ImuData.timestamp_ms[i-1]))
    XDriftData[i] = [ImuData.timestamp_ms[i], XAngleError]
XDriftDF = pd.DataFrame(XDriftData, columns=["timestamp_ms", "xangle_deg" ])

#Y angle error accumulation and dataframing the drift
YAngleError = 0.0
YDriftData = [[0.0, 0.0]] * ImuData.gyroy_dps.count()
for i in range(1, ImuData.gyroy_dps.count()):
    YAngleError = YAngleError + ((ImuData.gyroy_dps[i]/1000)*(ImuData.timestamp_ms[i] - ImuData.timestamp_ms[i-1]))
    YDriftData[i] = [ImuData.timestamp_ms[i], YAngleError]
YDriftDF = pd.DataFrame(YDriftData, columns=["timestamp_ms", "yangle_deg" ])

#Z angle error accumulation and dataframing the drift
ZAngleError = 0.0
ZDriftData = [[0.0, 0.0]] * ImuData.gyroz_dps.count()
for i in range(1, ImuData.gyroz_dps.count()):
    ZAngleError = ZAngleError + ((ImuData.gyroz_dps[i]/1000)*(ImuData.timestamp_ms[i] - ImuData.timestamp_ms[i-1]))
    ZDriftData[i] = [ImuData.timestamp_ms[i], ZAngleError]
ZDriftDF = pd.DataFrame(ZDriftData, columns=["timestamp_ms", "zangle_deg" ])

plt.figure()
plt.xlabel("Timestamp (ms)")
plt.ylabel("Angle Error (deg)")
plt.plot(XDriftDF.timestamp_ms, XDriftDF.xangle_deg, label = "X")
plt.plot(YDriftDF.timestamp_ms, YDriftDF.yangle_deg, label = "Y")
plt.plot(ZDriftDF.timestamp_ms, ZDriftDF.zangle_deg, label = "Z")
plt.legend()
plt.title("Resting Gyroscope Angle Drift")
plt.savefig("gyro_drift.png")
plt.show()