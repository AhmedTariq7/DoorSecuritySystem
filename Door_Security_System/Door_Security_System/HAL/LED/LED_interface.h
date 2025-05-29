
/*
 * LED_interface.h
 *
 * Created: 11/30/2024 6:46:02 PM
 *  Author: 37med
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/DIO/DIO_reg.h"
#include "../../MCAL/DIO/DIO_interface.h"


void LED_voidON    (u8 copy_u8port,u8 copy_u8pin);
void LED_voidOFF   (u8 copy_u8port,u8 copy_u8pin);
void LED_voidTOGGLE(u8 copy_u8port,u8 copy_u8pin);