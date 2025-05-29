/*
 * LCD_interface.h
 *
 * Created: 12/9/2024 7:54:16 PM
 *  Author: 37med
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* select LCD MODE */

#define  LCD_4BIT_MODE     0
#define  LCD_8BIT_MODE     1


#define  LCD_MODE     LCD_4BIT_MODE

/*********************************************/



void LCD_voidInit(void);

void LCD_voidSendCommand(u8 copy_u8command);

void LCD_voidSendData(u8 copy_u8data);

void LCD_voidSendString(u8*str);

void LCD_voidSendNumber(u32 number);

void LCD_voidGotoXY(u8 copy_u8x,u8 copy_u8y);

void LCD_voidDrawData(u8 copy_u8pattern, u8 *P_u8data,u8 copy_u8x, u8 copy_u8y);

#endif /* LCD_INTERFACE_H_ */