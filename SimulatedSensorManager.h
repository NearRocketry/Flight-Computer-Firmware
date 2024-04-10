#ifndef SENSOR_MANAGER
#define SENSOR_MANAGER

#include "LinearAlgebra.h"
#include "TrajectorySimulator.h"
#include <stdlib.h>

#define STANDARD_DEVIATION_CONSTANT 0.288675

#define ACCELEROMETER_BIAS 0.196 // bias in ms^-2
#define ACCELEROMETER_NOISE_RMS 0.0427 // noise in ms^-2
#define ACCELEROMETER_CROSS_AXIS 0.01

#define GYROSCOPE_BIAS 0.00873 // bias in radians per second
#define GYROSCOPE_NOISE_RMS 0.00288 // noise in radians per second
#define GYROSCOPE_CROSS_AXIS 0.002

#define BAROMETER_BIAS 33.3333
#define BAROMETER_NOISE_RMS 2
#define GROUND_PRESSURE_RMS 150
#define NORMAL_GROUND_PRESSURE 101325
#define PRESSURE_EXPONENT 3.50057556648
#define TEMEPERATURE_LAPSE_RATE 0.00976
#define GROUND_TEMPERATRURE 25
#define GROUND_TEMEPERATURE_RMS 3

float sensorTime;

typedef struct {
    vec3 accelerometerBias;
    matrix accelerometerCrossAxis;
    vec3 gyroscopeBias;
    matrix gyroscopeCrossAxis;
    float barometerBias;
    float groundPressure;
    float groundTemperature;
} sensorValues;

sensorValues sensorData;

float normalDestribution(float average, float standardDeviation, int iterations);
vec3 randomVector(float averageMagnitude, float standardDeviation);
void InitializeSensorManager();
void UpdateSensorData(float dt);
vec3 ReadAcceleration();
vec3 ReadAngularVelocity();
vec3 ReadMagneticField();
float ReadTemperature();
float ReadPressure();
vec3 ReadPosition();

#endif