#include "InertialMeasurementSystem.h"

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
    InitializeSensorManager();
}

void UpdateSystemEstimate(float deltaTime) {
    UpdateSensorData(deltaTime);

    vec3 acceleration = ReadAcceleration();
    vec3 angularVelocity = ReadAngularVelocity();
}

InertialMeasurementSystem GetEstimate(){
	return ims;
}
