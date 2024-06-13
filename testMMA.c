#include "MKL46Z4.h"
#include "I2C.h"
#include "MMA8451.h"
#include "math.h"
#include "delay.h"
#include "led.h"
#include "SLCD.h"
#include "switch.h"

volatile uint8_t op;

int main(void){
	LED_Init();
	Switch_Init();
	Systick_Init();
	SLCD_Init();
	I2C_Init(I2C0);
	MMAInit();
	delay(1);
	
	while(1){
		if (op == 1) {
			int16_t x_1 = MMA_x();
			delay(1);
			int16_t y_1 = MMA_y();
			delay(1);
			int16_t z_1 = MMA_z();
			delay(1);
			
			float x = (float) (x_1) / 4096;
			float y = (float) (y_1) / 4096;
			float z = (float) (z_1) / 4096;
			
			float val = sqrt(x*x + y*y + z*z);
			
			if (val > 2.5) {
				SLCD_Char('1');
				op = 2;
				while(op == 2);
			}
		}
		delay(1);
	}
}

