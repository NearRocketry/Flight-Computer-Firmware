#ifndef TRAJECTORY_SIMULATOR
#define TRAJECTORY_SIMULATOR

#include "LinearAlgebra.h"

#define DELTA_TIME 0.0001

typedef struct {
    vec3 position, velocity, acceleration;
    quat rotation;
    vec3 angularVelocity, angularAcceleration;
} trajectoryLocation;

trajectoryLocation trajectory;

vec3 PositionFunction(float time);
quat RotationFunction(float time);
void UpdateTrajectory(float time);

#endif