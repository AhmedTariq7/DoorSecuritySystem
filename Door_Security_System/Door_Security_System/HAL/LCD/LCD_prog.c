/*
 * LCD_prog.c
 *
 * Created: 12/9/2024 7:54:40 PM
 *  Author: AMIT
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#define  F_CPU 16000000UL 
#include <util/delay.h>



static void LCD_voidSHData(u8 copy_u8data){
	
	 u8 LOC_u8LcdPins[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN} ; 
	 u8 loc_in=0 ; 
	 
	 for (loc_in=0 ; loc_in<4;loc_in++)
	 {
															  
		 DIO_voidSetPinVal(LCD_DPORT,LOC_u8LcdPins[loc_in],GET_BIT(copy_u8data,loc_in)) ; 
		 
	 }
}

void LCD_voidSendEnablePluse(){
	
	  /*send enable pluse */
	  DIO_voidSetPinVal(LCD_CPORT,LCD_E_PIN,HIGH) ;
	  _delay_ms(2) ;
	  DIO_voidSetPinVal(LCD_CPORT,LCD_E_PIN,LOW) ;
	
}

void LCD_voidInit(void){
	
	_delay_ms(40) ; 
	
	 #if LCD_MODE ==LCD_8BIT_MODE
	/* send function set command */
	LCD_voidSendCommand(0x38) ;   ////
	
	#elif LCD_MODE == LCD_4BIT_MODE 
	   LCD_voidSHData(0b0010) ; 
	   LCD_voidSendEnablePluse() ; 
	   LCD_voidSHData(0b0010) ;
	   LCD_voidSendEnablePluse() ;
	   LCD_voidSHData(0b1000) ; 
	   LCD_voidSendEnablePluse() ;
	   #endif
	
	/* send  display ON/OFF command */
	LCD_voidSendCommand(0x0C) ; 
	/* Send CLR command */
	LCD_voidSendCommand(1) ; 
	
	
	
	
}


void LCD_voidSendCommand(u8 copy_u8command){
	
	/* set RS PIN as LOW TO SEND COMMAND */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,LOW) ; 
	/* set rw pin as low to write command */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;
	
	#if LCD_MODE == LCD_8BIT_MODE 
	/*send command  */
	DIO_voidSetPortVal(LCD_DPORT,copy_u8command) ; 
	  LCD_voidSendEnablePluse() ; 
	#elif LCD_MODE == LCD_4BIT_MODE 
	   LCD_voidSHData(copy_u8command>>4) ; 
	  LCD_voidSendEnablePluse() ;
	   LCD_voidSHData(copy_u8command) ;
	  LCD_voidSendEnablePluse() ;
	  #endif
	  
	
}




void LCD_voidSendData(u8 copy_u8data){

	/* set RS PIN as HIGH TO SEND DATA */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,HIGH) ;
	/* set rw pin as low to write command */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;
	
	#if LCD_MODE == LCD_8BIT_MODE
	/*send command  */
	DIO_voidSetPortVal(LCD_DPORT,copy_u8data) ;
	LCD_voidSendEnablePluse() ;
	#elif LCD_MODE == LCD_4BIT_MODE
	LCD_voidSHData(copy_u8data>>4) ;
	LCD_voidSendEnablePluse() ;
	LCD_voidSHData(copy_u8data) ;
	LCD_voidSendEnablePluse() ;
	#endif
	
	
}


void LCD_voidSendString(u8 *str){
	
	 u8 i=0 ; 
	
	 while(str[i] != '\0')      /* fathi  ----> f a t h i  \0 */
	  {
		  LCD_voidSendData(str[i]) ; 
		  i++ ; 
	  }
}



void LCD_voidSendNumber(u32 number) {
	u8 NumArray[10];   
	u8 NumPointer = 0; 
	
	
	if (number == 0)
	{
		NumArray[NumPointer++] = '0'; // if number = 0 store 0 ascii '48' in the array
	} 
	else 
	{
		while (number != 0) {
			NumArray[NumPointer++] = (number % 10) + '0'; // using mod to get the most right digit
			number /= 10; 
		}
	}

	// reverse the array
	for (u8 i = 0; i < NumPointer / 2; i++) 
	{
		u8 temp = NumArray[i];
		NumArray[i] = NumArray[NumPointer - i - 1];
		NumArray[NumPointer - i - 1] = temp;
	}

	NumArray[NumPointer] = '\0';
	
	LCD_voidSendString(NumArray);
}


void LCD_voidGotoXY(u8 copy_u8x,u8 copy_u8y){
	
	
	u8 DDRAM_address =0;
	
	DDRAM_address= copy_u8x + 0x40 * copy_u8y;
	
	
	SET_BIT(DDRAM_address,7);
	
	
	LCD_voidSendCommand(DDRAM_address);
	
	
}

void LCD_voidDrawData(u8 copy_u8pattern, u8 *P_u8data,u8 copy_u8x, u8 copy_u8y){
	u8 CGRAM_address =0;
	u8 copy_u8in=0;
	
	// calc pattern address
	CGRAM_address = copy_u8pattern * 8;
	
	// set CGRAM
	CLR_BIT(CGRAM_address,7);
	SET_BIT(CGRAM_address,6);
	LCD_voidSendCommand(CGRAM_address);
	
	// Draw data
	for(copy_u8in=0;copy_u8in<8;copy_u8in++){
		LCD_voidSendData(P_u8data[copy_u8in]);
	}
	
	// set DDRAM
	LCD_voidGotoXY(copy_u8x,copy_u8y);
	LCD_voidSendData(copy_u8pattern);
	
}