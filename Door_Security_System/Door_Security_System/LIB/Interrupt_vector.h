/*
 * Interrupt_vector.h
 *
 * Created: 12/21/2024 11:18:00 AM
 *  Author: AMIT
 */ 


#ifndef INTERRUPT_VECTOR_H_
#define INTERRUPT_VECTOR_H_

#define  ISR(__vector_NUM)      void __vector_NUM( void )__attribute__((signal)); \
                                void __vector_NUM (void)



#define   _INT0            __vector_1 
#define   _INT1            __vector_2
#define   _INT2            __vector_3
#define  TIMER2_COMP       __vector_4






#endif /* INTERRUPT_VECTOR_H_ */