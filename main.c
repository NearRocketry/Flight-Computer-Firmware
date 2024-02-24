#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SimulatedInertialMeasurementSystem.h"
#include "LocalSaveSystem.h"

long long getTime() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

int loop(InertialMeasurementSystem* system, long long* t) {
    float deltaTime = (getTime() - *t) * 0.000000001;
    *t = getTime();
    if (deltaTime < 0) return 0;
    UpdateSystemEstimate(deltaTime);
    
    return 0;
}

int main() {
    InitializeSaveSystemWrite("data.txt");

    quat rotation = {0, 0, 0, 1};
    vec3 angularVelocity = {0, 0, 0};
    vec3 angularAcceleration = {4 * 3.14, 0, 0};
    InitilizeInertialMeasurementSystem(rotation, angularVelocity, angularAcceleration);

    int looping = 0;
    long long t = getTime();
    long long start = getTime();
    while (!looping) {
        float size = qLen(ims.rotation);
        float data[6] = {t - start, ims.rotation.x, ims.rotation.y, ims.rotation.z, ims.rotation.w, size};
        SaveData(data, 6);
        looping = loop(&ims, &t);
        if (getTime() - start > 1000000000) looping = 1;
    }

    CloseSaveSystemWrite();
    GraphSaveData();
    return 0;
}