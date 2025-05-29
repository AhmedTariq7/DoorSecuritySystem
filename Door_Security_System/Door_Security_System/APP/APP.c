/*
 * APP.c
 *
 * Created: 3/26/2025 1:51:51 PM
 *  Author: 37med
 */ 
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
	0x00, 0x00, 0x00, 0x0A,
	0x04, 0x0A, 0x00, 0x00
};

void main() {
	// Set buzzer
	DIO_voidSetPinDir(DIO_PORTA, DIO_PIN3, OUTPUT);

	// Set LEDs
	DIO_voidSetPinDir(DIO_PORTC, DIO_PIN2, OUTPUT);
	DIO_voidSetPinDir(DIO_PORTC, DIO_PIN7, OUTPUT);
	DIO_voidSetPinDir(DIO_PORTD, DIO_PIN3, OUTPUT);

	// Set buttons
	DIO_voidSetPinDir(DIO_PORTB, DIO_PIN0, INPUT);
	DIO_voidSetPinVal(DIO_PORTB, DIO_PIN0, LOW);

	// Set and start LCD
	DIO_voidSetPortDir(LCD_DPORT, 0xf0);
	DIO_voidSetPortDir(LCD_CPORT, 0x0E);
	LCD_voidInit();

	// Start keypad
	KEYPAD_voidInit();

	// Turn on LED indicator
	LED_voidON(DIO_PORTB, DIO_PIN2);

	check();
}

// Function to get user input
void getUserPassword(u8 *userinput, u8 size) {
	u8 key, index = 0;
	
	LCD_voidSendCommand(1); // Clear screen
	LCD_voidGotoXY(0, 0);
	LCD_voidSendString("Enter Password");
	LCD_voidGotoXY(0, 1);
	LCD_voidSendString(": ");
	LCD_voidGotoXY(2, 1);

	while (index < size) {
		key = KEYPAD_u8GetKey();
		if (key != 0xff) {
			userinput[index] = key;
			LCD_voidSendNumber(key);
			_delay_ms(500);
			LCD_voidDrawData(0, dot, index + 1, 1);
			index++;
		}
	}

	// Wait for the user to confirm input
	while (DIO_u8ReadPinVal(DIO_PORTB, DIO_PIN0) == 0);
}

// Function to check if the entered password is correct
u8 isPasswordCorrect(u8 *password, u8 *userinput, u8 size) {
	for (int i = 0; i < size; i++) {
		if (password[i] != userinput[i]) {
			return 0; // Password incorrect
		}
	}
	return 1; // Password correct
}

// Function to handle wrong password attempts
void handleWrongAttempt(u8 attemptCount) {
	if (attemptCount == 0) LED_voidOFF(DIO_PORTC, led0);
	else if (attemptCount == 1) LED_voidOFF(DIO_PORTC, led1);
	else if (attemptCount == 2) LED_voidOFF(DIO_PORTD, led2);

	LCD_voidSendCommand(1); // Clear screen
	LCD_voidGotoXY(0, 0);
	LCD_voidSendString("Wrong Password");
	_delay_ms(2000);
}

// Function to trigger alert after 3 failed attempts
void triggerAlert() {
	LCD_voidSendCommand(1); // Clear screen
	LCD_voidGotoXY(0, 0);
	LCD_voidSendString("Alert!");

	while (1) {
		LED_voidTOGGLE(DIO_PORTC, DIO_PIN2);
		LED_voidTOGGLE(DIO_PORTC, DIO_PIN7);
		LED_voidTOGGLE(DIO_PORTD, DIO_PIN3);
		DIO_voidTogglePinVal(DIO_PORTA, DIO_PIN3);
		_delay_ms(200);
	}
}

// Main function to check password
void check() {
	u8 password[] = {1, 2, 3, 4}, userinput[4] = {};
	u8 passwordsize = sizeof(password) / sizeof(password[0]);
	u8 attemptCount = 0;

	LED_voidON(DIO_PORTC, led0);
	LED_voidON(DIO_PORTC, led1);
	LED_voidON(DIO_PORTD, led2);

	while (1) {
		getUserPassword(userinput, passwordsize);

		if (isPasswordCorrect(password, userinput, passwordsize)) {
			LCD_voidSendCommand(1); // Clear screen
			LCD_voidGotoXY(0, 0);
			LCD_voidSendString("Welcome");
			_delay_ms(1000);
			
			/*
				here the user should access the system to control the functions
			*/
			
			break; // Exit as password is correct
			} else {
			attemptCount++;
			handleWrongAttempt(attemptCount);

			if (attemptCount >= 3) {
				triggerAlert();
			}
		}
	}
}
