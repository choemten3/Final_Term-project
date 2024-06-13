#include "MKL46Z4.h"
#include "led.h"
#include "switch.h"
#include "delay.h"

volatile uint32_t delay_tick;
volatile uint32_t green_led = 0;
volatile uint32_t red_led = 0;

void Systick_Init(void) {
	// Enable Systick Interupt
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //(1 << 1)
	
	// Choose clock source for Systick (processor clock)
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; //(1<<2)
	
	// LOAD the count value (start)
	SysTick->LOAD = SystemCoreClock/1000 - 1;	// SystemCoreClock is approximately 21MHz by default
	
}

void SysTick_Handler(void) {
	delay_tick++;
	if (green_led == 500) {
		green_led = 0;
		PTD->PTOR |= 1 << 5;
	}
	green_led++;
	if (op == 2) {
		red_led++;
		if (red_led == 250) {
			red_led = 0;
			PTE->PTOR |= 1 << 29;
		}
	}
}

void delay(uint32_t delay_time) {
	while (delay_tick < delay_time);
	delay_tick = 0;
}


void Systick_Unactive(void) {
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Systick_Active(void) {
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
