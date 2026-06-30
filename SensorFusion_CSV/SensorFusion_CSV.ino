#include <Wire.h>
#include "SparkFun_BMI270_Arduino_Library.h"

BMI270 imu;
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;

float pastTime;

//gyro angle initialization
float gyroAngleX = 0.0;
float gyroAngleY = 0.0;
float gyroAngleZ = 0.0;

//complimentary filter initialization
float compAngleX;
float compAngleY;
float alpha = 0.98;

//kalman filter setup so we can have the same variable with differnt structures
struct KalmanFilter
{
float p00;
float p11;
float p01 = 0.0;
float p10 = 0.0;
float b = 0.0;
float theta;
float Q_angle;
//standard starting value is .003 because we do not have ennough testing to find
float Q_bias = 0.003;
float R;
};

KalmanFilter kalmanX;
KalmanFilter kalmanY;

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  while(imu.beginI2C(i2cAddress) != BMI2_OK)
  {
    delay(1000);
  }

  imu.getSensorData();
  pastTime = millis();

  //complimetary filter setup
  compAngleX = atan2(imu.data.accelY, imu.data.accelZ) * (180/M_PI);
  compAngleY = atan2(imu.data.accelX, imu.data.accelZ) * (180/M_PI);
  kalmanX.theta = compAngleX; //starting angles are off of the accel
  kalmanY.theta = compAngleY;
  //noise of gyro coming from variance of angle coming from the gyro noise floor test
  kalmanX.Q_angle = 2.88e-6;
  kalmanY.Q_angle = 3.24e-6;
  //noise of accel coming from variance of angle from static hold test
  kalmanX.R = 0.00304;
  kalmanY.R = 0.00315;
  //setting the itial p00 value to the steady state value to which p00 prev = p00. Solved on paper
  kalmanX.p00 = sqrt(kalmanX.R * kalmanX.Q_angle);
  kalmanY.p00 = sqrt(kalmanY.R * kalmanY.Q_angle);
  //P11 is less of a big hitter, but changing it closer to the equilibrium value will be helpful in the start
  kalmanX.p11 = kalmanX.Q_bias;
  kalmanY.p11 = kalmanY.Q_bias;
}


void loop()
{
  imu.getSensorData();
  float currentTime = millis();
  float dt = (currentTime - pastTime)/1000;

  //timestamp printing
  Serial.print(currentTime);
  Serial.print(",");

  //GyroX Only Angle
  gyroAngleX = gyroAngleX + (imu.data.gyroX * dt);
  Serial.print(gyroAngleX, 3);
  Serial.print(",");

  //GyroY Only Angle
  gyroAngleY = gyroAngleY + (imu.data.gyroY * dt);
  Serial.print(gyroAngleY, 3);
  Serial.print(",");

  //GyroZ Only Angle
  gyroAngleZ = gyroAngleZ + (imu.data.gyroZ * dt);
  Serial.print(gyroAngleZ, 3);
  Serial.print(",");

  //AccelX Only Angle
  float accelAngleX = atan2(imu.data.accelY, imu.data.accelZ) * (180/M_PI);
  Serial.print(accelAngleX, 3);
  Serial.print(",");

  //AccelY Only Angle
  float accelAngleY = atan2(imu.data.accelX, imu.data.accelZ) * (180/M_PI);
  Serial.print(accelAngleY, 3);
  Serial.print(",");

  //Complimentary Filter Fusion AngleX
  compAngleX = (alpha * (compAngleX + (imu.data.gyroX * dt))) + ((1 - alpha) * accelAngleX);
  Serial.print(compAngleX, 3);
  Serial.print(",");

  //Complimentary Filter Fusion AngleX
  compAngleY = (alpha * (compAngleY + (imu.data.gyroY * dt))) + ((1 - alpha) * accelAngleY);
  Serial.print(compAngleY, 3);
  Serial.print(",");



  //kalman filter x
  //predict phase
  float theta_pred = kalmanX.theta + ((imu.data.gyroX - kalmanX.b) * dt);
  float b_pred = kalmanX.b;
  //p_pred = A x p x AT + Q uncertainty growing during predict phase
  float p00_pred = kalmanX.p00 - (kalmanX.p10 * dt) - (kalmanX.p01 * dt) + ((dt*dt) * kalmanX.p11) + kalmanX.Q_angle;
  float p01_pred = kalmanX.p01 - (kalmanX.p11 * dt);
  float p10_pred = kalmanX.p10 - (kalmanX.p11 * dt);
  float p11_pred = kalmanX.p11 + kalmanX.Q_bias;

  //update phase
  float y = accelAngleX - theta_pred; //innovation: distance between predicted gyro value and accel value
  float s = p00_pred + kalmanX.R; // place holder for combination of gyro noise(p00) and accel noise(R)

  float K0 = p00_pred/s; //High K0 indicates accel should be trusted as most of the noise is coming from gyro
  float K1 = p10_pred/s; //high K1 indicates high angle and bias uncertainty correlation relative to noise

  kalmanX.theta = theta_pred + (K0 * y); //pulls gyro toward accel a certain amount based on k0
  kalmanX.b = b_pred + (K1 * y); //changes bias based on correlation to angle uncertainty correlation and measurment dissagreement

//p = (I - K x H) x p_pred uncertainty shrinking after measurment
  kalmanX.p00 = (1-K0) * p00_pred; //angle uncertainty tuned based on how much the accel is trusted
  kalmanX.p01 = (1-K0) * p01_pred; // correlation is based on how much accel is trusted
  kalmanX.p10 = kalmanX.p01; //mathmatically the matrix should be symetric. This is just forcing that so the computer doesnt allow p10 and p01 to differ
  kalmanX.p11 = p11_pred - (K1 * p10_pred); //bias uncertainty drops when correlation between angle uncertainty and bias uncertainty is high meanign we know our bias well when correlation is high

  //printing the kalman filter values
  Serial.print(kalmanX.theta, 3);
  Serial.print(",");
  
  
  //kalman filter y
  //predict phase
  theta_pred = kalmanY.theta + ((imu.data.gyroY - kalmanY.b) * dt);
  b_pred = kalmanY.b;
  //p_pred = A x p x AT + Q uncertainty growing during predict phase
  p00_pred = kalmanY.p00 - (kalmanY.p10 * dt) - (kalmanY.p01 * dt) + ((dt*dt) * kalmanY.p11) + kalmanY.Q_angle;
  p01_pred = kalmanY.p01 - (kalmanY.p11 * dt);
  p10_pred = kalmanY.p10 - (kalmanY.p11 * dt);
  p11_pred = kalmanY.p11 + kalmanY.Q_bias;

  //update phase
  y = accelAngleY - theta_pred; //innovation: distance between predicted gyro value and accel value
  s = p00_pred + kalmanY.R; // place holder for combination of gyro noise(p00) and accel noise(R)

  K0 = p00_pred/s; //High K0 indicates accel should be trusted as most of the noise is coming from gyro
  K1 = p10_pred/s; //high K1 indicates high angle and bias uncertainty correlation relative to noise

  kalmanY.theta = theta_pred + (K0 * y); //pulls gyro toward accel a certain amount based on k0
  kalmanY.b = b_pred + (K1 * y); //changes bias based on correlation to angle uncertainty correlation and measurment dissagreement

//p = (I - K x H) x p_pred uncertainty shrinking after measurment
  kalmanY.p00 = (1-K0) * p00_pred; //angle uncertainty tuned based on how much the accel is trusted
  kalmanY.p01 = (1-K0) * p01_pred; // correlation is based on how much accel is trusted
  kalmanY.p10 = kalmanY.p01; //mathmatically the matrix should be symetric. This is just forcing that so the computer doesnt allow p10 and p01 to differ
  kalmanY.p11 = p11_pred - (K1 * p10_pred); //bias uncertainty drops when correlation between angle uncertainty and bias uncertainty is high meanign we know our bias well when correlation is high

  //printing the kalman filter values
  Serial.println(kalmanY.theta, 3);
  
  //CSV order: timestamp(ms),gyrox(deg),gyroy(deg),gyroz(deg),accelx(deg),accely(deg),compfilterx(deg),compfiltery(deg), kalmanx(deg), kalmany(deg)

  pastTime = currentTime;
  delay(20);
}
