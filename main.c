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
    srand(time(NULL));
    InitializeSaveSystemWrite("data.txt");
    InitilizeInertialMeasurementSystem();
    printf("accelerometer bias %f %f %f", sensorData.accelerometerBias.x, sensorData.accelerometerBias.y, sensorData.accelerometerBias.z);

    int looping = 0;
    long long t = getTime();
    long long start = getTime();
    while (!looping) {
        float size = qLength(ims.rotation);
        float data[4] = {t - start, ims.position.x, ims.position.y, ims.position.z};
        SaveData(data, 4);
        looping = loop(&ims, &t);
        if (getTime() - start > 10000000000) looping = 1;
    }

    CloseSaveSystemWrite();
    GraphSaveData();
    return 0;
}