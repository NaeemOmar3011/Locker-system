/*
 * KEYPAD_cfg.h
 *
 * Created: 8/31/2023 1:41:03 PM
 *  Author: N A E E M
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_
#include "generic_macros_header.h"

#define KEYPAD_port_init() DDRD =0b11110000; \
						 PORTD =0b11111111; 	

#define KEYPAD_1(x) if(x==0) CLRBIT(PORTD,PD4); else SETBIT(PORTD,PD4);
#define KEYPAD_2(x) if(x==0) CLRBIT(PORTD,PD5); else SETBIT(PORTD,PD5);
#define KEYPAD_3(x) if(x==0) CLRBIT(PORTD,PD6); else SETBIT(PORTD,PD6);
#define KEYPAD_4(x) if(x==0) CLRBIT(PORTD,PD7); else SETBIT(PORTD,PD7);

#define KEYPAD_A READBIT(PIND,PD0)
#define KEYPAD_B READBIT(PIND,PD1)
#define KEYPAD_C READBIT(PIND,PD2)
#define KEYPAD_D READBIT(PIND,PD3)



#endif /* KEYPAD_CFG_H_ */