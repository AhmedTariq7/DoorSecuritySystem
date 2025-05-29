
/*
 * LED_prog.c
 *
 * Created: 11/30/2024 6:46:15 PM
 *  Author: 37med
 */ 

#include "LED_interface.h"


void LED_voidON	   (u8 copy_u8port,u8 copy_u8pin){
	DIO_voidSetPinDir(copy_u8port,copy_u8pin,OUTPUT);
	DIO_voidSetPinVal(copy_u8port,copy_u8pin,HIGH);
}
void LED_voidOFF   (u8 copy_u8port,u8 copy_u8pin){
	DIO_voidSetPinDir(copy_u8port,copy_u8pin,OUTPUT);
	DIO_voidSetPinVal(copy_u8port,copy_u8pin,LOW);
}
void LED_voidTOGGLE(u8 copy_u8port,u8 copy_u8pin){
	DIO_voidSetPinDir(copy_u8port,copy_u8pin,OUTPUT);
	DIO_voidTogglePinVal(copy_u8port,copy_u8pin);
}
