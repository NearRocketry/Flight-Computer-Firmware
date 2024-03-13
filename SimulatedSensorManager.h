#ifndef SENSOR_MANAGER
#define SENSOR_MANAGER

#include "LinearAlgebra.h"
#include "TrajectorySimulator.h"

float sensorTime;

void UpdateSensorData(float dt) {
    sensorTime += dt;
    UpdateTrajectory(sensorTime);
}

vec3 ReadAcceleration() {
    vec3 result = qRotateVector(trajectory.acceleration, trajectory.rotation);
    return result;
}

vec3 ReadAngularVelocity() {
    vec3 result = trajectory.angularVelocity;
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