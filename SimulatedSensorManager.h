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

float normalDestribution(float average, float standardDeviation, int iterations) {
    float result = 0;
    for (int i = 0; i < iterations; i++) {
        result += (float) rand() / RAND_MAX;
    }
    result -= 0.5 * iterations;
    result *= standardDeviation / (sqrt(iterations) * STANDARD_DEVIATION_CONSTANT);
    result += average;
    return result;
}

vec3 randomVector(float averageMagnitude, float standardDeviation) {
    float mainAngle = acos(2 * (float) rand() / RAND_MAX - 1);
    float secondAngle = 2 * PI * rand() / RAND_MAX;
    float magnitude = normalDestribution(averageMagnitude, standardDeviation, 10);
    return vPolar(mainAngle, secondAngle, magnitude);
}

void InitializeSensorManager() {
    // initialize the decalibration values for accelerometer
    sensorData.accelerometerBias = randomVector(0, ACCELEROMETER_BIAS);
    matrix accelerometerCrossAxis = 
    {{1 - pow(normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), 2), normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10)},
    {normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), 1 - pow(normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), 2), normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10)},
    {normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), 1 - pow(normalDestribution(0, ACCELEROMETER_CROSS_AXIS, 10), 2)}};
    sensorData.accelerometerCrossAxis = accelerometerCrossAxis;
    // initialize the decalibration values for gyroscope
    sensorData.gyroscopeBias = randomVector(0, GYROSCOPE_BIAS);
    matrix gyroscopeCrossAxis = 
    {{1 - pow(normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), 2), normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10)},
    {normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), 1 - pow(normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), 2), normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10)},
    {normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), 1 - pow(normalDestribution(0, GYROSCOPE_CROSS_AXIS, 10), 2)}};
    sensorData.gyroscopeCrossAxis = gyroscopeCrossAxis;
    // initialize the decalibration values for barometer
    sensorData.barometerBias = normalDestribution(0, BAROMETER_BIAS, 10);
    sensorData.groundPressure = normalDestribution(NORMAL_GROUND_PRESSURE, GROUND_PRESSURE_RMS, 10);
    sensorData.groundTemperature = normalDestribution(GROUND_TEMPERATRURE, GROUND_TEMEPERATURE_RMS, 10);
}

void UpdateSensorData(float dt) {
    sensorTime += dt;
    UpdateTrajectory(sensorTime);
}

vec3 ReadAcceleration() {
    vec3 gravity = {0, 0, 0 * -9.81};
    vec3 result = qRotateVector(vAdd(trajectory.acceleration, gravity), trajectory.rotation);
    result = mApply(sensorData.accelerometerCrossAxis, result);
    result = vAdd(result, sensorData.accelerometerBias);
    result = vAdd(result, randomVector(0, ACCELEROMETER_NOISE_RMS));
    return result;
}

vec3 ReadAngularVelocity() {
    vec3 result = trajectory.angularVelocity;
    result = mApply(sensorData.gyroscopeCrossAxis, result);
    result = vAdd(result, sensorData.gyroscopeBias);
    result = vAdd(result, randomVector(0, GYROSCOPE_NOISE_RMS));
    return result;
}

vec3 ReadMagneticField() {
    
}

float ReadTemperature() {

}

float ReadPressure() {
    float height = trajectory.position.z;
    float pressure = sensorData.groundPressure * powf(1 - height * TEMEPERATURE_LAPSE_RATE / sensorData.groundTemperature, PRESSURE_EXPONENT);
    pressure += sensorData.barometerBias + normalDestribution(0, BAROMETER_NOISE_RMS, 10);
    return pressure;
}

vec3 ReadPosition() {
    vec3 result = trajectory.position;
    return result;
}

#endif