#include "MKL46Z4.h"
#include "led.h"

void LED_Init(void) {
	SIM->SCGC5 |= 1 << 12;
	SIM->SCGC5 |= 1 << 13;
	
	PORTD->PCR[5] |= 1 << 8;
	PORTE->PCR[29] |= 1 << 8;
	
	PTD->PDDR |= (1 << 5);
	PTE->PDDR |= (1 << 29);
	
	PTE->PSOR |= (1 << 29);
	PTD->PSOR |= (1 << 5);
}
