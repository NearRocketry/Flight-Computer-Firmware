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

void UpdateTrajectory(float time) {
    trajectory.position = PositionFunction(time);
    trajectory.velocity = vDivide(DELTA_TIME, vSubtract(PositionFunction(time + DELTA_TIME), PositionFunction(time)));
    trajectory.acceleration = vDivide(DELTA_TIME * DELTA_TIME, vAdd(vSubtract(PositionFunction(time + 2 * DELTA_TIME), vScale(2, PositionFunction(time + DELTA_TIME))), PositionFunction(time)));

    trajectory.rotation = RotationFunction(time);
    quat rotationChange = qMultiply(RotationFunction(time + DELTA_TIME), qConjugate(RotationFunction(time)));
    float angle = acos(rotationChange.w);
    trajectory.angularVelocity = vScale(angle / sin(angle) / DELTA_TIME ,vQuat(rotationChange));
}

vec3 PositionFunction(float time) {

}

quat RotationFunction(float time) {

}

#endif