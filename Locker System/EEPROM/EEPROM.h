/*
 * EEPROM.h
 *
 * Created: 8/18/2023 12:44:34 PM
 *  Author: safifi
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "generic_macros_header.h"

void EEPROM_write(uint16_t add, uint8_t data);
uint8_t EEPROM_read(uint16_t add);



#endif /* EEPROM_H_ */