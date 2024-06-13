#include "MKL46Z4.h"
#include "SLCD.h"

const char pin[] = {37, 17, 7, 8, 53, 38, 10, 11, 40, 52, 19, 18};

char wf_table[] =
{
    0x0B, 0x0E,     
    0x0A, 0,
	0, 0,
};

void SLCD_Init(void) {
	SIM->SCGC5 |= 1 << 19 | 1 << 10 | 1 << 11 | 1 << 12 | 1 << 13;
	
	LCD->GCR = 1 << 6 | 0x03;
	MCG->C1 |= 1 << 1;

	
	
	// Enable PIN for frontplane and backplane
	LCD->PEN[1] |= 1 << 5;	//37		
	LCD->PEN[0] |= 1 << 17;		//17	
	LCD->PEN[1] |= 1 << 8;			//40
	LCD->PEN[1] |= 1 << 20;		//52
	LCD->PEN[0] |= 1 << 19;			//19
	LCD->PEN[0] |= 1 << 18;			//18
	
	LCD->BPEN[1] |= 1 << 8;			
	LCD->BPEN[1] |= 1 << 20;		
	LCD->BPEN[0] |= 1 << 19;		
	LCD->BPEN[0] |= 1 << 18;		
	
	// Turn on all backplane
	LCD->WF8B[40] = 1 << 0;
	LCD->WF8B[52] = 1 << 1;
	LCD->WF8B[19] = 1 << 2;
	LCD->WF8B[18] = 1 << 3;
	
	// Enable LCD
	LCD->GCR |=	1 << 7; 			
}

void SLCD_Char(char character) {
	int index;
	if (character == ' ') {
		index = 4;
	} else {
		index = (character - '0') * 2;
	}
	char wf;
	
    wf = wf_table[index];	
    LCD->WF8B[37] = wf;
    wf = wf_table[index + 1];	
    LCD->WF8B[17] = wf;
    
}
