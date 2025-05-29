/*
 * KEYPAD_prog.c
 *
 * Created: 12/14/2024 10:26:44 AM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_config.h"


u8 KEYPAD_DATA_ARR[4][4]={{1,2,3,'+'},
	                      {4,5,6,'-'},
					      {7,8,9,'*'},
					      {'C',0,'=','/'}} ; 


void KEYPAD_voidInit(void){
	
	    u8 COL_ARR[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN} ; 
	    u8 ROW_ARR[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN} ;
	    
	     u8 LOCu8row=0 , LOC_u8col=0 ; 
		 
		 for (LOC_u8col=0 , LOCu8row=0 ; LOCu8row<4 && LOC_u8col<4 ; LOC_u8col++,LOCu8row++)
		 { 
			 /* make rows pins as input & active internal pull up */
			 DIO_voidSetPinDir(KEYPAD_ROW_PORT,ROW_ARR[LOCu8row],INPUT) ; 
			 DIO_voidSetPinVal(KEYPAD_ROW_PORT,ROW_ARR[LOCu8row],HIGH) ; 
			 
			 /*make colums as output high */
			 DIO_voidSetPinDir(KEYPAD_COL_PORT,COL_ARR[LOC_u8col],OUTPUT) ; 
			 DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[LOC_u8col],HIGH)  ;  
		 }
}

u8 KEYPAD_u8GetKey(void){
	
	 u8 COL_ARR[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN} ;
	 u8 ROW_ARR[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN} ;
	 
	 u8 LOCu8row=0 , LOC_u8col=0 ;
	 
	 u8 LOC_u8val=0xff ; 
	 
	 for (LOC_u8col=0 ; LOC_u8col<4 ;LOC_u8col++)
	 {
		 /* set col(n) ---> low */
		 DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[LOC_u8col],LOW) ; 
		 
		 for(LOCu8row=0 ; LOCu8row<4;LOCu8row++){
			 
			 /* CHECK IF  button is pressed */
			 
			   if(DIO_u8ReadPinVal(KEYPAD_ROW_PORT,ROW_ARR[LOCu8row])==0){
				   LOC_u8val=KEYPAD_DATA_ARR[LOCu8row][LOC_u8col] ; 
				   // cancel debouncing
				   while(DIO_u8ReadPinVal(KEYPAD_ROW_PORT,ROW_ARR[LOCu8row])==0) ; 
				   return LOC_u8val ;    
			   }		 
		 }
		  /* set col(n) ---> HIGH */
		  DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[LOC_u8col],HIGH) ;
		 
	 }
	
	return LOC_u8val ; 
	
}
