/*
 * LCD_config.h
 *
 * Created: 12/9/2024 7:54:27 PM
 *  Author: AMIT
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* data pins  FOR 4 bit mode d4 ----> d7 */
#define  LCD_DPORT    DIO_PORTA 

#if LCD_MODE == LCD_4BIT_MODE 
#define  LCD_DPORT    DIO_PORTA 
#define  LCD_D4_PIN   DIO_PIN4
#define  LCD_D5_PIN   DIO_PIN5
#define  LCD_D6_PIN   DIO_PIN6
#define  LCD_D7_PIN   DIO_PIN7
#endif 


/*control pins */
#define  LCD_CPORT    DIO_PORTA 
#define LCD_RS_PIN    DIO_PIN2
#define LCD_RW_PIN    DIO_PIN1
#define LCD_E_PIN     DIO_PIN0





#endif /* LCD_CONFIG_H_ */