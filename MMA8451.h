#include "MKL46Z4.h"
#ifndef MMA8451_H
#define MMA8451_H

// Transmit and Receive
void MMAWrite(uint8_t addr, uint8_t data);
uint8_t MMARead(uint8_t addr);

// Initiate
void MMAInit(void);

// Collect Data
int16_t MMA_Read_Reg16(uint8_t reg);
// x Axis
int16_t MMA_x(void);
// y Axis
int16_t MMA_y(void);
// z Axis
int16_t MMA_z(void);

#endif 