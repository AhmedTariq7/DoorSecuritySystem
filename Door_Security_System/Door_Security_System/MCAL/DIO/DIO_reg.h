/*
 * DIO_reg.h
 *
 * Created: 11/30/2024 9:46:21 AM
 *  Author: AMIT
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

/* GROUP A */

#define  PORTA_REG        *((volatile u8*)0x3B)
#define  DDRA_REG         *((volatile u8*)0x3A)
#define  PINA_REG         *((volatile u8*)0x39)


/* GROUP B */

#define  PORTB_REG        *((volatile u8*)0x38)
#define  DDRB_REG         *((volatile u8*)0x37)
#define  PINB_REG         *((volatile u8*)0x36)

/* GROUP B */

#define  PORTC_REG        *((volatile u8*)0x35)
#define  DDRC_REG         *((volatile u8*)0x34)
#define  PINC_REG         *((volatile u8*)0x33)


/* GROUP D */

#define  PORTD_REG        *((volatile u8*)0x32)
#define  DDRD_REG         *((volatile u8*)0x31)
#define  PIND_REG         *((volatile u8*)0x30)




#endif /* DIO_REG_H_ */