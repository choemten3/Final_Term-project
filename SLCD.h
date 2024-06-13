#include "MKL46Z4.h"

#define SEGDP 0x01	// Phase A as DP
#define SEGC  0x02	// Phase B as Segment C
#define SEGB  0x04	// Phase C as Segment B
#define SEGA  0x08	// Phase D as Segment A
                  
#define SEGD  0x01	// Phase A as Segment D
#define SEGE  0x02	// Phase B as Segment E
#define SEGG  0x04	// Phase C as Segment G
#define SEGF  0x08	// Phase D as Segment F

void SLCD_Init(void);
void SLCD_Char(char character);
