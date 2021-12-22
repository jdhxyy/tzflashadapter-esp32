// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// tzflash������
// Authors: jdh99 <jdh821@163.com>

#include "tzflashadapter.h"
#include "tzflash.h"

#include <string.h>

#include "esp_partition.h"
#include "esp_system.h"

#define PAGE_SIZE 4096
#define ALIGN_NUM 1

#define PARTITION_NAME_LEN_MAX 32

static char gPartitionName[PARTITION_NAME_LEN_MAX] = {0};

// eraseFlash ����flash
// addr:��ʼ��ַ.size:�����ֽ���
// �ɹ�����true,ʧ�ܷ���false
static bool eraseFlash(uint32_t addr, int size);

// writeFlash д��flash
// addr:��ʼ��ַ.bytes:��д����ֽ���.size:д���ֽ���
// �ɹ�����true,ʧ�ܷ���false
static bool writeFlash(uint32_t addr, uint8_t* bytes, int size);

// readFlash ��ȡflash
// addr:��ʼ��ַ.bytes:��ȡ���ֽ�����ŵĻ���.size:��ȡ���ֽ���
// �ɹ�����true,ʧ�ܷ���false
static bool readFlash(uint32_t addr, uint8_t* bytes, int size);

// TZFlashAdapterLoad ģ������.partitionName�Ƿ�����
bool TZFlashAdapterLoad(char* partitionName) {
    if (strlen(partitionName) > PARTITION_NAME_LEN_MAX - 1) {
        return false;
    }
    strcpy(gPartitionName, partitionName);
    return TZFlashLoad(PAGE_SIZE, ALIGN_NUM, eraseFlash, writeFlash, readFlash);
}

// TZFlashEraseFlash ����flash
// addr:��ʼ��ַ.size:�����ֽ���
// �ɹ�����true,ʧ�ܷ���false
bool TZFlashEraseFlash(uint32_t addr, int size) {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, 
        ESP_PARTITION_SUBTYPE_ANY, gPartitionName);
    if (partition == NULL) {
        return false;
    }
    if (addr + size > partition->size || addr % PAGE_SIZE != 0 || size % PAGE_SIZE != 0) {
        return false;
    }
    
    return esp_partition_erase_range(partition, addr, size) == ESP_OK;
}

// TZFlashWriteFlash д��flash
// addr:��ʼ��ַ.bytes:��д����ֽ���.size:д���ֽ���
// �ɹ�����true,ʧ�ܷ���false
bool TZFlashWriteFlash(uint32_t addr, uint8_t* bytes, int size) {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, 
        ESP_PARTITION_SUBTYPE_ANY, gPartitionName);
    if (partition == NULL) {
        return false;
    }
    if (addr + size > partition->size) {
        return false;
    }

    return esp_partition_write(partition, addr, bytes, size) == ESP_OK;
}

// TZFlashReadFlash ��ȡflash
// addr:��ʼ��ַ.bytes:��ȡ���ֽ�����ŵĻ���.size:��ȡ���ֽ���
// �ɹ�����true,ʧ�ܷ���false
bool TZFlashReadFlash(uint32_t addr, uint8_t* bytes, int size) {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, 
        ESP_PARTITION_SUBTYPE_ANY, gPartitionName);
    if (partition == NULL) {
        return false;
    }
    if (addr + size > partition->size) {
        return false;
    }

    return esp_partition_read(partition, addr, bytes, size) == ESP_OK;
}
