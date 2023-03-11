#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MUART_interface.h"
#include "MDIO_interface.h"
#include "util/delay.h"

#define F_CPU  8000000UL

//Identify the recieved bit from mobile app
u8_t access ;


//This function is used to display LEDs
void display_status(u8_t access)
 {
	mdio_setPinStatus(PORTB, PIN0 | PIN1 | PIN2, OUTPUT );

	mdio_setPinValue(PORTB, PIN0, LOW);
	mdio_setPinValue(PORTB, PIN1, LOW);
	mdio_setPinValue(PORTB, PIN2, LOW);

	/*If the user-name and password are correct*/
	if(access == 'A' || access == '1'|| access == '0')
	{
		mdio_setPinValue(PORTB, PIN0, HIGH);
		mdio_setPinValue(PORTB, PIN1, LOW);
		mdio_setPinValue(PORTB, PIN2, LOW);
	}
	/*If the user-name and password are incorrect*/
	else if(access == 'W')
	{
		mdio_setPinValue(PORTB, PIN0, LOW);
		mdio_setPinValue(PORTB, PIN1, HIGH);
		mdio_setPinValue(PORTB, PIN2, LOW);
	}
	/*If the user-name and password are incorrect for three times*/
	else if(access == 'E')
	{
		mdio_setPinValue(PORTB, PIN0, LOW);
		mdio_setPinValue(PORTB, PIN1, LOW);
		mdio_setPinValue(PORTB, PIN2, HIGH);

	}
	else
	{
		/*Do nothing*/
	}

	/*return from this function*/
	return;
 }

//This function is used to move motor
void move_motor(u8_t direction)
 {
	 mdio_setPinStatus(PORTA, PIN0, OUTPUT);
	 mdio_setPinStatus(PORTC, PIN0, OUTPUT);

	 mdio_setPinValue(PORTA, PIN0, LOW);
	 mdio_setPinValue(PORTC, PIN0, LOW);

	 //Open door
	 if(direction == '1')
	 {
		 mdio_setPinValue(PORTA, PIN0, HIGH);
		 mdio_setPinValue(PORTC, PIN0, LOW);
	 }
	 //Close door
	 else if(direction == '0')
	 {
		 mdio_setPinValue(PORTA, PIN0, LOW);
		 mdio_setPinValue(PORTC, PIN0, HIGH);
	 }
	 else
	 {
		 /*Do nothing*/
	 }

	 /*Return from this function*/
	 return;
 }






int main(void)
{
	mdio_setPinStatus(PORTD, PIN0, INPUT_FLOAT);
	mdio_setPinStatus(PORTD, PIN1, OUTPUT);
	muart_init(UART_9600_BPS);

	while(1)
	{
		muart_recvByte(&access);
		display_status(access);
		move_motor(access);

	}

	return 0;
}
