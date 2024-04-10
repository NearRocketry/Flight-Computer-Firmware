#include "TrajectorySimulator.h"

vec3 PositionFunction(float time) {
    vec3 result = {0, 0, 0};
    return result;
}

quat RotationFunction(float time) {
    quat result = {1, 0, 0, 0};
    return result;
}

void UpdateTrajectory(float time) {
    trajectory.position = PositionFunction(time);
    trajectory.velocity = vDivide(DELTA_TIME, vSubtract(PositionFunction(time + DELTA_TIME), PositionFunction(time)));
    trajectory.acceleration = vDivide(DELTA_TIME * DELTA_TIME, vAdd(vSubtract(PositionFunction(time + 2 * DELTA_TIME), vScale(2, PositionFunction(time + DELTA_TIME))), PositionFunction(time)));

    trajectory.rotation = RotationFunction(time);
    quat rotationChange = qMultiply(RotationFunction(time + DELTA_TIME), qConjugate(RotationFunction(time)));
    float angle = acos(rotationChange.w);
    trajectory.angularVelocity = vScale(angle / sin(angle) / DELTA_TIME ,vQuat(rotationChange));
}