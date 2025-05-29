#define F_CPU 16000000UL
#include <util/delay.h>

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LCD/LCD_config.h"


#define led0 DIO_PIN2
#define led1 DIO_PIN7
#define led2 DIO_PIN3


u8 dot[] = {
	0x00,
	0x00,
	0x00,
	0x0A,
	0x04,
	0x0A,
	0x00,
	0x00
};

void main(){
		
		//set buzzer
		DIO_voidSetPinDir(DIO_PORTA,DIO_PIN3,OUTPUT);
		
		//set leds
		DIO_voidSetPinDir(DIO_PORTC,DIO_PIN2,OUTPUT);
		DIO_voidSetPinDir(DIO_PORTC,DIO_PIN7,OUTPUT);
		DIO_voidSetPinDir(DIO_PORTD,DIO_PIN3,OUTPUT);
		
		//set buttons
		DIO_voidSetPinDir(DIO_PORTB,DIO_PIN0,INPUT);
		DIO_voidSetPinVal(DIO_PORTB,DIO_PIN0,LOW);
		
		//set and start lcd 
		DIO_voidSetPortDir(LCD_DPORT,0xf0);
		DIO_voidSetPortDir(LCD_CPORT,0x0E);
		LCD_voidInit();
		
		//start keypad
		KEYPAD_voidInit();
		
		LED_voidON(DIO_PORTB,DIO_PIN2);
		check();
}




void check() {
	
	u8 LOC_u8C = 0, Ptrue = 1, key = 0xff;
	u8 password[] = {1, 2, 3, 4}, userinput[4] = {};
	u8 passwordsize = sizeof(password) / sizeof(password[0]);
	u8 attemptCount = 0; // Counter for wrong attempts
	
	LED_voidON(DIO_PORTC,led0);
	LED_voidON(DIO_PORTC,led1);
	LED_voidON(DIO_PORTD,led2);
	
	
	while (1) {
		LOC_u8C = 0;
		Ptrue = 1; // Assume the password is correct initially
		
		LCD_voidSendCommand(1); // Clear screen
		LCD_voidGotoXY(0, 0);
		LCD_voidSendString("Enter Password");
		LCD_voidGotoXY(0, 1);
		LCD_voidSendString(": ");
		LCD_voidGotoXY(2, 1);
		
		while (LOC_u8C < passwordsize) {
			LCD_voidGotoXY(LOC_u8C + 1, 1);
			key = KEYPAD_u8GetKey();
			if (key != 0xff) {
				userinput[LOC_u8C] = key;
				LCD_voidSendNumber(key);
				_delay_ms(500);
				LCD_voidDrawData(0,dot,LOC_u8C + 1, 1);
				LOC_u8C++;
			}
		}
		
		// Wait for button press connected to PORTB pin 0 to check password
		while (DIO_u8ReadPinVal(DIO_PORTB,DIO_PIN0)==0);
		
		for (int i = 0; i < passwordsize; i++) {
			if (password[i] != userinput[i]) {
				Ptrue = 0; // Password is incorrect
			}
		}
		
		LCD_voidSendCommand(1); // Clear screen
		LCD_voidGotoXY(0, 0);
		
		if (Ptrue == 1) {
			LCD_voidSendString("Welcome");
			_delay_ms(2000);
			break; // Exit the loop as password is correct
			} else {
			if(attemptCount==0)		 LED_voidOFF(DIO_PORTC,led0);
			else if(attemptCount==1) LED_voidOFF(DIO_PORTC,led1);
			else if(attemptCount==2) LED_voidOFF(DIO_PORTD,led2);
			attemptCount++;
			LCD_voidSendString("Wrong Password");
			_delay_ms(2000);
			
			if (attemptCount >= 3) {
				
				LCD_voidSendCommand(1); // Clear screen
				LCD_voidGotoXY(0, 0);
				LCD_voidSendString("Alert!");
				while (1){
					LED_voidTOGGLE(DIO_PORTC,DIO_PIN2);
					LED_voidTOGGLE(DIO_PORTC,DIO_PIN7);
					LED_voidTOGGLE(DIO_PORTD,DIO_PIN3);
					DIO_voidTogglePinVal(DIO_PORTA,DIO_PIN3);
					_delay_ms(200);
				}
			}
		}
	}
}

