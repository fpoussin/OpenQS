#ifndef COMMON_H
#define COMMON_H

#include "ch.h"
#include "hal.h"

inline uint32_t leToInt(uint8_t *ptr);
inline uint32_t beToInt(uint8_t *ptr);
uint8_t checksum(uint8_t *data, uint8_t length);
int32_t uitoa(uint32_t value, char * buf, uint32_t max);
int32_t itoa(int32_t value, char * buf, int32_t max);

#endif