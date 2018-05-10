#ifndef COMMON_H
#define COMMON_H

#include "Vector.h"

#define WIDTH 128
#define HEIGHT 32

#define BATT_PIN A0
#define BATT_MAX 710
#define BATT_MIN 430

// Compass data
const float declination = 4.58f;
float heading = 0.0f;

// Oritentation data
vec3 look = { 0, 0, 0 };

// Position data
vec3 pos = { 0, 0, 0 };
vec3 dest = { 0, 0, 1000000.0f };

// Other data 
float temp = 0.0f;

/* IMU Data */
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double magX, magY, magZ;
int16_t tempRaw;

double roll, pitch, yaw; // Roll and pitch are calculated using the accelerometer while yaw is calculated using the magnetometer

double gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro only
double compAngleX, compAngleY, compAngleZ; // Calculated angle using a complementary filter
double kalAngleX, kalAngleY, kalAngleZ; // Calculated angle using a Kalman filter

#endif
