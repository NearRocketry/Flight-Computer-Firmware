#ifndef INERTIAL_MEASUREMENT_SYSTEM_H
#define INERTIAL_MEASUREMENT_SYSTEM_H

#include "LinearAlgebra.h"
#include "SimulatedSensorManager.h"

typedef struct {
    /*vec3 position, velocity, acceleration, force;*/
   quat rotation;
   vec3 angularVelocity, angularAcceleration;
} InertialMeasurementSystem;

InertialMeasurementSystem ims;

void RotateInTime(float deltaTime) {
    vec3 rotationVector = vScale(deltaTime, ims.angularVelocity);
    quat deltaRotation = qPolar(rotationVector);
    ims.rotation = qMul(deltaRotation, ims.rotation);
    ims.rotation = qNorm(ims.rotation);
}

void InitilizeInertialMeasurementSystem(quat rotation, vec3 angularVelocity, vec3 angularAcceleration) {
    ims.rotation = rotation;
    ims.angularVelocity = angularVelocity;
    ims.angularAcceleration = angularAcceleration;
}

void UpdateSystemEstimate(float deltaTime) {
    RotateInTime(0.5 * deltaTime);
    ims.angularVelocity = vAdd(ims.angularVelocity, vScale(deltaTime, ims.angularAcceleration));
    RotateInTime(0.5 * deltaTime);
}

#endif