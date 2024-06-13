#include "MKL46Z4.h"

void Set_Master(I2C_Type *obj);
void Set_Slave(I2C_Type *obj);

void Set_Tx(I2C_Type *obj);
void Set_Rx(I2C_Type *obj);

void I2C_Init(I2C_Type *obj);

uint8_t I2C_Read(I2C_Type *obj);
void I2C_Write(I2C_Type *obj, uint8_t data);

void send_ACK(I2C_Type *obj);
void send_NACK(I2C_Type *obj);
void Repeated_Start(I2C_Type *obj);

void Start(I2C_Type *obj);
void Stop(I2C_Type *obj);
void WaitFlagACK(I2C_Type *obj);
