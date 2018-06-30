// Assume using ATMega32 "AVR"
// To interface with the serial monitor, we should use UART
// Using LED connected with PORTD (PD7)
// The LED is active low
// The Switch is connected with PORTD (PD2)
// In ATMega32 PD2 can be used as external interrupt

#include <avr/io.h>         //library for i/o
#include <avr/interrupt.h>  //library for interrupt
#include  <util/delay.h>    //library for delay

//--------------- The Driver of UART (Prototypes) ------------------
void Uart_init(long BaudRate);
void UART_send_byte( char byte);
void UART_send_string( char *ptr);
//------------------------------------------------------------------

int main()
{
	DDRD  = (1<<PD7);    //Data Direction Register is set to 1 for the LED as output.
	PORTD = (1<<PD7);    //Data Register is set to 1 for the LED.
	GICR  = (1<<INT0);   //General interrupt Control Register the pin INT0 is set to 1
					 	           //to enable its interrupt this pin is responsible for the external
					             //interrupt connected here with a switch in pin PD2.
	MCUCR = 0x02;        //MCU Control Register 0x02 to make INT0 falling edge triggered.
	sei();			         //Enable interrupts, opens the global interrupt.

	Uart_init(9600);     //Setting the Baud rate up.
	UART_send_string("OFF");

	while(1);		         //wait here.

	return 0;
}

ISR(INT0_vect)		     //ISR for external interrupt INT0.
{
  _delay_ms(500);      //for debouncing of the switch.
	UART_send_string("pressed");
	PORTD &=~ (1<<PD7);  //Turn the LED on.
	UART_send_string("ON");
}

//--------------------- The Driver of UART -------------------------
void Uart_init(long BaudRate)
{
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL=(unsigned char)(((F_CPU)/(16*BaudRate))-1);
}

void UART_send_byte( char byte)
{
	while(!(UCSRA &(1<<UDRE))); // while shift register flag != 1 (not empty))
	UDR=byte;
}

void UART_send_string( char *ptr)
{
	int i=0;
	while(ptr[i] != '\0')
	{
		UART_send_byte(ptr[i]);
		i++;
	}
	UART_send_byte(ptr[i]);
}
//------------------------------------------------------------------
