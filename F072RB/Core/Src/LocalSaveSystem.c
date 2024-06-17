#include "LocalSaveSystem.h"

void InitializeSaveSystemWrite(char* filename) {
    filePath = fopen(filename, "w");

    if (filePath == NULL) {
        fprintf(stderr, "Error: Failed to open!\n");
        exit(1);
    }
}

void SaveData(float* data, int dataLength) {
    for (int i = 0; i < dataLength; i++) {
        fprintf(filePath, "%f", (float)data[i]);
        if (i + 1 < dataLength) fprintf(filePath, ",");
        else fprintf(filePath, "\n");
    }
}

void CloseSaveSystemWrite() {
    fclose(filePath);
}

void GraphSaveData() {
    system("python3.11 plot.py");
}