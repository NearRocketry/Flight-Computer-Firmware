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

void UpdateSensorData(float t) {
    sensorTime = t;
    
    // elyptic path
    float eccentricity = 1.5;
    location.position = {eccentricity * cos(t), sin(t), 0};
}

vec3 ReadAcceleration() {

}

vec3 ReadAngularVelocity() {

}

vec3 ReadMagneticField() {

}

float ReadTemperature() {

}

float ReadPressure() {

}

#endif