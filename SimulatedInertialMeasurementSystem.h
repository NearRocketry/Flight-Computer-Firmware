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
}

void UpdateSystemEstimate(float deltaTime) {
    UpdateSensorData(deltaTime);

    vec3 acceleration = ReadAcceleration(sensorTime);
    vec3 angularVelocity = ReadAngularVelocity(sensorTime);

    quat endRotation = qMultiply(qPolar(vScale(deltaTime, angularVelocity)), ims.rotation);
    vec3 rotatedAcceleration = qRotateVector(acceleration, endRotation);
    
    ims.position = vAdd(ims.position, vScale(0.25 * deltaTime, ims.velocity));
    ims.velocity = vAdd(ims.velocity, vScale(0.5 * deltaTime, ims.acceleration));
    ims.position = vAdd(ims.position, vScale(0.25 * deltaTime, ims.velocity));

    ims.rotation = qPolarRotation(vScale(0.5 * deltaTime, ims.angularVelocity), ims.rotation);

    ims.acceleration = ReadAcceleration();
    ims.angularVelocity = ReadAngularVelocity();

    ims.position = vAdd(ims.position, vScale(0.25 * deltaTime, ims.velocity));
    ims.velocity = vAdd(ims.velocity, vScale(0.5 * deltaTime, ims.acceleration));
    ims.position = vAdd(ims.position, vScale(0.25 * deltaTime, ims.velocity));

    ims.rotation = qPolarRotation(vScale(0.5 * deltaTime, ims.angularVelocity), ims.rotation);
}

#endif