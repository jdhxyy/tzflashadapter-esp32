// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// tzflash������
// Authors: jdh99 <jdh821@163.com>

#ifndef TZFLASHADAPTER_H
#define TZFLASHADAPTER_H

#include <stdint.h>
#include <stdbool.h>

// TZFlashAdapterLoad ģ������.partitionName�Ƿ�����
bool TZFlashAdapterLoad(char* partitionName);

// TZFlashEraseFlash ����flash
bool TZFlashEraseFlash(uint32_t addr, int size);

// TZFlashWriteFlash д��flash
bool TZFlashWriteFlash(uint32_t addr, uint8_t* bytes, int size);

// TZFlashReadFlash ��ȡflash
bool TZFlashReadFlash(uint32_t addr, uint8_t* bytes, int size);

#endif
