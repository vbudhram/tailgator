/*
	LCD port definitons
	Connect E to bit 7 0f port.
	Connect RS to bit 6 of port.
	Connect R/W to bit 5 of port.
	Connect bits 3:0 of port to DB 7:4 of LCD.
*/
#define LCD_PORT	PORTC
#define LCD_DDR		DDRC

#define LED_PORT	PORTB
#define LED_DDR		DDRB

/*
	Motor port definitons
	A to PORTD0
	B to PORTD1
	C to PORTD2
	D to PORTD3

	EN1 to PORTD4
	EN2 to PORTD5

*/
#define MOTOR_PORT	PORTD
#define MOTOR_DDR DDRD
#define MOTOR_VALUE	PIND

/*
	Button
	ENTER to PORTB0
	UP to PORTB1
	DOWN to PORTB2
	BACK to PORTB3

	STOPLEFT to PORTB4
	STOPRIGHT to PORTB5

	LEDLIGHT_OUTPUT to PORTB6
*/
#define BUTTON_PORT	PORTB
#define BUTTON_DDR DDRB
#define BUTTON_VALUE	PINB

/*
	Analog to Digital port definitions
	AD0 to PORTA0
	AD1 to PORTA1
*/
#define AD_PORT	PORTA
#define AD_DDR	DDRA

void PORT_init(void)
{

	LCD_PORT = 0x00;
	LCD_DDR = 0xFF;
	
	MOTOR_PORT = 0x00;
	MOTOR_DDR = 0x7F;

	BUTTON_PORT = 0x00;
	BUTTON_DDR = 0b01000000;
	
}
