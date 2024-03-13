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

float sensorTime;

typedef struct {
    vec3 accelerometerBias;
    vec3 gyroscopeBias;
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
    sensorData.accelerometerBias = randomVector(0, ACCELEROMETER_BIAS);
    sensorData.gyroscopeBias = randomVector(0, GYROSCOPE_BIAS);
}

void UpdateSensorData(float dt) {
    sensorTime += dt;
    UpdateTrajectory(sensorTime);
}

vec3 ReadAcceleration() {
    vec3 gravity = {0, 0, 9.81};
    vec3 result = vAdd(qRotateVector(trajectory.acceleration, trajectory.rotation), gravity);
    result = qRotateVector(result, qPolar(randomVector(0, ACCELEROMETER_CROSS_AXIS)));
    result = vAdd(result, sensorData.accelerometerBias);
    result = vAdd(result, randomVector(0, ACCELEROMETER_NOISE_RMS));
    return result;
}

vec3 ReadAngularVelocity() {
    vec3 result = trajectory.angularVelocity;
    result = qRotateVector(result, qPolar(randomVector(0, GYROSCOPE_CROSS_AXIS)));
    result = vAdd(result, sensorData.gyroscopeBias);
    result = vAdd(result, randomVector(0, GYROSCOPE_NOISE_RMS));
    return result;
}

vec3 ReadMagneticField() {
    
}

float ReadTemperature() {

}

float ReadPressure() {

}

vec3 ReadPosition() {
    vec3 result = trajectory.position;
    return result;
}

#endif