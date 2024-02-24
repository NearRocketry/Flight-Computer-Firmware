#ifndef SENSOR_MANAGER
#define SENSOR_MANAGER

#include "LinearAlgebra.h"

float sensorTime;

typedef struct {
    vec3 position, velocity, acceleration;
    quat rotation;
    vec3 angularVelocity, angularAcceleration;
} actuallLocation;

actuallLocation location;

void UpdateSensorData(float dt) {
    sensorTime += dt;
    
    // circular path
    vec3 pos = {cos(sensorTime), sin(sensorTime), 0};
    location.position = pos;

    vec3 vel = {-sin(sensorTime), cos(sensorTime), 0};
    location.velocity = vel;

    vec3 acc = {-cos(sensorTime), -sin(sensorTime), 0};
    location.acceleration = acc;

    vec3 axis = {0, 0, 1};
    quat rot = qPolar(vScale(0 * sensorTime, axis));
    location.rotation = rot;

    vec3 angVel = vScale(0 * 1, axis);
    location.angularVelocity = angVel;

    vec3 angAcc = {0, 0, 0};
    location.angularAcceleration = angAcc;
}

vec3 ReadAcceleration() {
    return location.acceleration;
}

vec3 ReadAngularVelocity() {
    return location.angularVelocity;
}

vec3 ReadMagneticField() {
    
}

float ReadTemperature() {

}

float ReadPressure() {

}

#endif