Door Security System
Overview
This project implements a door security system using an AVR microcontroller (e.g., ATmega32). The system authenticates users by requiring Gros a 4-digit password via a keypad, controls LED indicators, and triggers a buzzer alarm after three incorrect attempts. It features an LCD display for user interaction, showing prompts and feedback.
Features

Password Entry: Users input a 4-digit password using a 4x4 keypad.
LCD Interface: Displays prompts ("Enter Password", "Welcome", "Wrong Password", "Alert!") and visual feedback for password entry.
LED Indicators: Three LEDs (on PORTC PIN2, PORTC PIN7, PORTD PIN3) indicate remaining attempts, turning off one by one with each incorrect entry.
Buzzer Alert: Activates a buzzer (on PORTA PIN3) and flashes LEDs after three failed password attempts.
Confirmation Button: A button (on PORTB PIN0) confirms password entry.
Keypad Support: Interfaces with a 4x4 keypad for password input.
Indicator LED: An LED (on PORTB PIN2) signals system initialization.

Hardware Requirements

Microcontroller: AVR (e.g., ATmega32) with a 16 MHz clock.
LCD: 16x2 LCD (configured via LCD_config.h).
Keypad: 4x4 matrix keypad.
LEDs: Four LEDs (three for attempts, one for system status).
Buzzer: Connected to PORTA PIN3.
Push Button: Connected to PORTB PIN0 for confirming input.
Power Supply: Stable 5V supply for the microcontroller and peripherals.

Software Requirements

Compiler: AVR-GCC for compiling the C code.
Libraries:
util/delay.h for delay functions.
Custom libraries: BIT_MATH.h, STD_TYPE.h, DIO_interface.h, LED_interface.h, LCD_interface.h, LCD_config.h, KEYPAD_interface.h.


Programming Tool: AVR programmer (e.g., USBasp) for flashing the microcontroller.

Installation

Clone the Repository:git clone https://github.com/yourusername/door-security-system.git


Configure Hardware:
Connect the LCD, keypad, LEDs, buzzer, and push button to the specified AVR ports (refer to APP.c for pin assignments).
Ensure the microcontroller is set to run at 16 MHz (F_CPU 16000000UL).


Compile and Upload:
Compile the code using AVR-GCC.
Flash the compiled .hex file to the microcontroller using an AVR programmer.


Power On: Apply power to the system and verify the indicator LED (PORTB PIN2) lights up.

Usage

Power On: The system initializes, and the indicator LED turns on.
Password Entry:
The LCD displays "Enter Password".
Enter a 4-digit password using the keypad.
Each digit is displayed briefly, then replaced with a dot for security.
Press the confirmation button (PORTB PIN0) to submit the password.


Authentication:
If the password matches {1, 2, 3, 4}, the LCD displays "Welcome", and the system grants access.
If incorrect, an LED turns off, and the LCD shows "Wrong Password".
After three failed attempts, the system enters alert mode, flashing LEDs and sounding the buzzer indefinitely.


Reset: To retry after a wrong password (before three attempts), re-enter the password. After three failed attempts, a system reset is required.

File Structure

APP.c: Main application code handling password input, validation, and system control.
LIB/:
BIT_MATH.h: Bit manipulation macros.
STD_TYPE.h: Standard type definitions.


MCAL/DIO/:
DIO_interface.h: Digital I/O interface functions.


HAL/:
LED/LED_interface.h: LED control functions.
LCD/LCD_interface.h, LCD_config.h: LCD control and configuration.
KEYPAD/KEYPAD_interface.h: Keypad control functions.



Notes

The default password is {1, 2, 3, 4} (hardcoded in APP.c). Modify the password array in the check() function to change it.
The system uses a 16 MHz clock frequency (F_CPU 16000000UL). Adjust if using a different frequency.
Ensure proper connections for the LCD, keypad, LEDs, and buzzer to avoid hardware issues.
The alert mode (after three failed attempts) runs indefinitely; a hardware reset is required to restart.

Future Improvements

Add EEPROM storage for a configurable password.
Implement a timeout for password entry.
Add a mechanism to exit alert mode without a full reset.
Support multiple user passwords or admin override.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Contributing
Contributions are welcome! Please submit a pull request or open an issue for suggestions or bug reports.
