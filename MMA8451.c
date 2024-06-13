#include "MKL46Z4.h"
#include "I2C.h"
#include "delay.h"
#define MMA_ADDR							(0x1D << 1)
#define I2C_WRITE							0
#define I2C_READ							1

// Transmit and Receive
void MMAWrite(uint8_t addr, uint8_t data){
	delay(1);
	Start(I2C0);
	
	// i2c_write(I2C0, MAG3110_I2C_ADDR<<1);
	I2C_Write(I2C0, MMA_ADDR);
	I2C_Write(I2C0, addr);
	
	I2C_Write(I2C0, data);
	
	Stop(I2C0);
}

uint8_t MMARead(uint8_t addr){
	delay(1);
	Start(I2C0);
	// 6 bit Device Address and 1 bit Write + ACK
	I2C_Write(I2C0, MMA_ADDR | I2C_WRITE);
	
	// 7 bit Register Address + ACK
	I2C_Write(I2C0, addr);
	
	// 1 bit SR
	Repeated_Start(I2C0);
	
	//6 bit Device Address + 1 bit Read + ACK
	I2C_Write(I2C0, MMA_ADDR | I2C_READ);
	
	// Chuyen sang qua trinh nhan du lieu
	Set_Rx(I2C0);
	
	//Send bit NACK for Slave
	send_NACK(I2C0);
	
	I2C_Read(I2C0);
	
	// delay to wait I2C0
	WaitFlagACK(I2C0);
	
	uint8_t data = I2C_Read(I2C0);
	// delay to wait I2C0
	WaitFlagACK(I2C0);
	
	Stop(I2C0);
	
	return data;
}

// Init
void MMAInit(void){
	MMAWrite(0x2A, 0x01);
}

// Collect Data
int16_t MMA_Read_Reg16(uint8_t reg){
	int16_t result = MMARead(reg);
	result = ((int16_t)(result<<8) | MMARead(reg + 1)) >> 2;
	return result;
}

// x Axis
int16_t MMA_x(void){
	return MMA_Read_Reg16(0x01);
}

// y Axis
int16_t MMA_y(void){
	return MMA_Read_Reg16(0x03);
}

// z Axis
int16_t MMA_z(void){
	return MMA_Read_Reg16(0x05);
}
