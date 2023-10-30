/*
 * EEPROM.c
 *
 * Created: 8/18/2023 12:44:20 PM
 *  Author: safifi
 */ 
#include "EEPROM.h"

void EEPROM_write(uint16_t add, uint8_t data){
	while(READBIT(EECR,EEWE) == 1); // busy
	EEAR = add;
	EEDR = data;
	SETBIT(EECR, EEMWE);
	SETBIT(EECR, EEWE);
}

uint8_t EEPROM_read(uint16_t add){
	while(READBIT(EECR,EEWE) == 1); // busy
	EEAR = add;
	SETBIT(EECR, EERE);
	return 	EEDR;	
}