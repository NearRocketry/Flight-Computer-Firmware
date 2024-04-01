#ifndef INERTIAL_MEASUREMENT_SYSTEM_H
#define INERTIAL_MEASUREMENT_SYSTEM_H

#include "LinearAlgebra.h"
#include "SimulatedSensorManager.h"

typedef struct {
    vec3 position, velocity, acceleration;
    quat rotation;
    vec3 angularVelocity, angularAcceleration;
} InertialMeasurementSystem;

InertialMeasurementSystem ims;

void RotateInTime(float deltaTime) {
    vec3 rotationVector = vScale(deltaTime, ims.angularVelocity);
    quat deltaRotation = qPolar(rotationVector);
    ims.rotation = qMultiply(deltaRotation, ims.rotation);
    ims.rotation = qNormalize(ims.rotation);
}

void InitilizeInertialMeasurementSystem() {
    InertialMeasurementSystem sys = {{1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, 0, 0, 1}, {0, 0, 0}, {0, 0, 0}};
    ims = sys;
    sensorTime = 0;
    InitializeSensorManager();
}

void UpdateSystemEstimate(float deltaTime) {
    UpdateSensorData(deltaTime);

    vec3 acceleration = ReadAcceleration();
    vec3 angularVelocity = ReadAngularVelocity();
}

#endif