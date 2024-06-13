#include "MKL46Z4.h"
#include "delay.h"
#include "switch.h"
#include "SLCD.h"
#include "led.h"
#include "i2c.h"


void Switch_Init(void) {
	op = 0;
	
	SIM->SCGC5 |= 1 << 11;
	
	PORTC->PCR[3] |= 1 << 8;
	PORTC->PCR[12] |= 1 << 8;

	PORTC->PCR[3] |= 1 << 0;
	PORTC->PCR[3] |= 1 << 1;
	PORTC->PCR[12] |= 1 << 0;
	PORTC->PCR[12] |= 1 << 1;

	PORTC->PCR[3] |= PORT_PCR_IRQC(0xA);
	PORTC->PCR[12] |= PORT_PCR_IRQC(0xA);
	
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);
	NVIC_SetPriority(PORTC_PORTD_IRQn, 1);

	PTC->PDDR &= (~(uint32_t)(1 << 3));
	PTC->PDDR &= (~(uint32_t)(1 << 12));
}

void PORTC_PORTD_IRQHandler(void) {
	if ((PTC->PDIR & (1 << 3)) == 0) {
		if (op == 0 ) {
			Systick_Active();
			PTD->PCOR |= 1 << 5;
			SLCD_Char('0');
			op = 1;
		} else if (op == 1) {
			Systick_Unactive();
			PTD->PSOR |= 1 << 5;
			SLCD_Char(' ');
			op = 0;
		}
		
	}
	if ((PTC->PDIR & (1 << 12)) == 0) {
		if (op != 0) {
			PTE->PSOR |= 1 << 29;
			SLCD_Char('0');
			op = 1;
		}
	}
	PORTC->PCR[3] |= 1 << 24;
	PORTC->PCR[12] |= 1 << 24;
}
