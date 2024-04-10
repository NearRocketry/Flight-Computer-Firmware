#include "SimulatedSensorManager.h"

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