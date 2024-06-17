#ifndef __INERTIAL_MEASUREMENT_SYSTEM_H
#define __INERTIAL_MEASUREMENT_SYSTEM_H

#include "LinearAlgebra.h"
#include "SimulatedSensorManager.h"

typedef struct {
    vec3 position, velocity, acceleration;
    quat rotation;
    vec3 angularVelocity, angularAcceleration;
} InertialMeasurementSystem;

void RotateInTime(float deltaTime);
void InitilizeInertialMeasurementSystem();
void UpdateSystemEstimate(float deltaTime);
InertialMeasurementSystem GetEstimate();

#endif
