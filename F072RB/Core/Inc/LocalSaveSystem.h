#ifndef __SAVE_SYSTEM_H
#define __SAVE_SYSTEM_H

#include <stdlib.h>
#include <stdio.h>

FILE* filePath;

void InitializeSaveSystemWrite(char* filename);
void SaveData(float* data, int dataLength);
void CloseSaveSystemWrite();
void GraphSaveData();

#endif
