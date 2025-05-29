/*
 * EXTI_prog1.c
 *
 * Created: 12/20/2024 11:52:12 AM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../../LIB/Interrupt_vector.h"
#include "EXTI_reg.h"
#include "EXTI_interface.h"


void (*EXTI_PTR[3])(void)={0};



void EXTI_voidInit( u8 copy_u8interrupt_num , u8 copy_u8sense){
	
	
	switch(copy_u8interrupt_num){
		
		case INT_0 : 
		              
					  if (copy_u8sense == LOW_LEVEL)
					  {
						  CLR_BIT(MCUCR_REG,0) ; 
						  CLR_BIT(MCUCR_REG,1) ;
						  
					  }
					  else if (copy_u8sense==ANY_LOGICAL_CHANGE)
					  {
						  SET_BIT(MCUCR_REG,0) ;
						  CLR_BIT(MCUCR_REG,1) ;
						  
					  }
					  else if (copy_u8sense == FALLING_EDGE)
					  {
						  CLR_BIT(MCUCR_REG,0) ;
						  SET_BIT(MCUCR_REG,1) ;
					  }
					  else if(copy_u8sense == RISING_EDGE){
						  
						  SET_BIT(MCUCR_REG,0) ;
						  SET_BIT(MCUCR_REG,1) ;
					  }
					  else{  }  break; 
						  
		case INT_1 :
		
		             if (copy_u8sense == LOW_LEVEL)
		             {
		             	CLR_BIT(MCUCR_REG,2) ;
		             	CLR_BIT(MCUCR_REG,3) ;
		             	
		             }
		             else if (copy_u8sense==ANY_LOGICAL_CHANGE)
		             {
		             	SET_BIT(MCUCR_REG,2) ;
		             	CLR_BIT(MCUCR_REG,3) ;
		             	
		             }
		             else if (copy_u8sense == FALLING_EDGE)
		             {
		             	CLR_BIT(MCUCR_REG,2) ;
		             	SET_BIT(MCUCR_REG,3) ;
		             }
		             else if(copy_u8sense == RISING_EDGE){
		             	
		             	SET_BIT(MCUCR_REG,2) ;
		             	SET_BIT(MCUCR_REG,3) ;
		             }
		             else{  }  break;
		             
		
		case INT_2 : 
		               if (copy_u8sense==FALLING_EDGE)
		               {
						   CLR_BIT(MCUCSR_REG,6) ; 
						   
		               }
					   else if (copy_u8sense==RISING_EDGE)
					   {
						   SET_BIT(MCUCSR_REG,6) ; 
					   }
		               else{
						   
					   }
		              break;
	}
	
	
	
	
}

void EXTI0_voidEnable(void){
	
	SET_BIT(GICR_REG,6) ; 
	
}
void EXTI0_voidDisable(void){
	
	CLR_BIT(GICR_REG,6) ;
	
}



void EXTI1_voidEnable(void){
	SET_BIT(GICR_REG,7);
}
void EXTI1_voidDisable(void){
	CLR_BIT(GICR_REG,7);
}



void EXTI2_voidEnable(void){
	SET_BIT(GICR_REG,5);
	
	
}
void EXTI2_voidDisable(void){
	
	
	CLR_BIT(GICR_REG,5);
	
	
}




void EXTI_voidsetCallBack(u8 EXTRNum,void (*ptr)(void)){
	
//	EXTI_PTR_0 = ptr;


	switch(EXTRNum){
		case INT_0 : 
			EXTI_PTR[0]=ptr;
			break;
		case INT_1 :
			EXTI_PTR[1]=ptr;
			break;
		case INT_2 :
			EXTI_PTR[2]=ptr;
			break;
		default:
			break;
	}
}



ISR(INT_0){
	EXTI_PTR[0]();
}

ISR(INT_1){
	EXTI_PTR[1]();
}

ISR(INT_2){
	EXTI_PTR[2]();
}
/*
void __vector_1 (void)__attribute__((signal));
void __vector_1 (void){
	EXTI_PTR[0]();
}

void __vector_2 (void)__attribute__((signal));
void __vector_2 (void){
	EXTI_PTR[1]();
}

void __vector_3 (void)__attribute__((signal));
void __vector_3 (void){
	EXTI_PTR[2]();
}
*/