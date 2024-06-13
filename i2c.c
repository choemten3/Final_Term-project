#include "MKL46Z4.h"

void Set_Master(I2C_Type *obj){
	obj->C1 |= I2C_C1_MST_MASK;
}

void Set_Slave(I2C_Type *obj){
	obj->C1 &= ~I2C_C1_MST_MASK;
}

void Set_Tx(I2C_Type *obj){
	obj->C1 |= I2C_C1_TX_MASK;
}

void Set_Rx(I2C_Type *obj){
	obj->C1 &= ~I2C_C1_TX_MASK;
}

void I2C_Init(I2C_Type *obj){
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; // 1 << 7 (bit so 6) Cap nguon cho i2c0
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);
	
	obj->C1 |= I2C_C1_IICEN_MASK;
}

uint8_t I2C_Read(I2C_Type *obj){
	return obj->D;
}

void I2C_Write(I2C_Type *obj, uint8_t data){
	obj->D = data;
	while((obj->S & I2C_S_IICIF_MASK) == 0);
	obj->S |= I2C_S_IICIF_MASK;
}

void send_ACK(I2C_Type *obj){
	obj->C1 &= ~I2C_C1_TXAK_MASK;
}

void send_NACK(I2C_Type *obj){
	obj->C1 |= I2C_C1_TXAK_MASK;
}

void Repeated_Start(I2C_Type *obj){
	obj->C1 |= (1u<<2);
}

void Start(I2C_Type *obj){
	Set_Tx(obj);
	Set_Master(obj);
}

void Stop(I2C_Type *obj){
	Set_Rx(obj);
	Set_Slave(obj);
}

void WaitFlagACK(I2C_Type *obj){
	while((obj->S & I2C_S_IICIF_MASK) == 0);
	obj->S |= I2C_S_IICIF_MASK;
}

