# Instructions for setting the app up:
- Using ATMega32 "AVR", so you need to burn the "main.c" file on the kit.
- You need To connect the LED with PORTD (PD7).
- You need to connect the Switch with PORTD (PD2).
- You need to connect the Serial monitor its Rx with the Tx pin in the ATMega32.

# Assumptions:
- The LED at the beginning is OFF.
- The LED operates as avtive low, when PD7 is set to 1 the LED is OFF.
- The Baud rate between ATMega32 and the serial monitor is 9600 bit/sec.
- The Interrupt will be happen at the falling edge.

# Known issue:
- I was testing a Push button, so in the ISR you will find a delay 500 ms it was put just for the debouncing of the button, so it can be     removed but it will not affect the performnce of the application.
