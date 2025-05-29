/*
 * GI_prog.c
 *
 * Created: 12/20/2024 11:38:53 AM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "GI_reg.h"



void  GI_voidEnable(void){
	
	SET_BIT(SREG_REG,L_BIT) ;  // SREG|=1<<7 ; 
	
	//__asm volatile("SEI") ; 
}
void  GI_voidDisable(void) {
	CLR_BIT(SREG_REG,L_BIT) ; 
	
	//__asm volatile("CLI") ;
	
}

