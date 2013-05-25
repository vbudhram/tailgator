#include <util/delay.h>

// LCD display commands.  Call as an argument with LCD_COMMAND() function.
// Example: LCD_COMMAND(LCD_CLEAR_HOME); will clear the screen and return the cursor to the start position.
// You may add commands by looking at the HD44780 LCD spec sheet for the hex codes.
#define LCD_CLEAR_HOME			0x01
#define LCD_HOME				0x02
#define LCD_CURSOROFF_BLINKOFF	0x0C



void LCD_COMMAND(char Byte)
{
	unsigned char ByteTemp;

	ByteTemp = Byte >> 4;				// Take upper nibble of byte by right shifting by four bits.
	LCD_PORT = ByteTemp;				// Write data to LCD_PORT
	LCD_PORT = ByteTemp | 0b10000000;	// Set clock bit (E) of LCD
	LCD_PORT = ByteTemp;				// Clear clock bit (E) of LCD
	ByteTemp = Byte & 0b00001111;      // Take lower nibble of byte by ANDing
	LCD_PORT = ByteTemp;				// Write data to LCD_PORT
	LCD_PORT = ByteTemp | 0b10000000;   // Set clock bit (E) of LCD
	LCD_PORT = ByteTemp;				// Clear clock bit (E) of LCD
	_delay_ms(5);						// Wait for 5 ms  
	return;
}

void LCD_CHARACTER(char Byte)
{
	unsigned char ByteTemp;

	ByteTemp = Byte >> 4;				// Take upper nibble of byte by right shifting by four bits.
	LCD_PORT = ByteTemp | 0b01000000;	// Write data to LCD_PORT
	LCD_PORT = ByteTemp | 0b11000000;	// Set clock bit (E) of LCD
	LCD_PORT = ByteTemp | 0b01000000;	// Clear clock bit (E) of LCD
	ByteTemp = Byte & 0b00001111;      	// Take lower nibble of byte by ANDing
	LCD_PORT = ByteTemp | 0b01000000;	// Write data to LCD_PORT
	LCD_PORT = ByteTemp | 0b11000000;   // Set clock bit (E) of LCD
	LCD_PORT = ByteTemp | 0b01000000;	// Clear clock bit (E) of LCD
	_delay_ms(2);						// Wait for 5 ms  
	return;
}

void LCD_STRING(char *String)
{
	int i=0;

	while(String[i] != 0x00)			// Check for NULL character at end of character string
	{
		LCD_CHARACTER(String[i]);		// Write each character to the LCD
		i++;
	}
	return;
}

void LCD_init(void)
{
	// These are configuration bytes used to initialize the LCD for 4-bit operation.  Do not change these.
	const unsigned char 	Byte1=0x33, Byte2=0x32, Byte3=0x28, Byte4=0x0f, Byte5=0x01;

	// Set LCD port as outputs
	LCD_DDR = 0xff;

	// Send the configuration bytes to the LCD
	LCD_COMMAND(Byte1);
	LCD_COMMAND(Byte2);
	LCD_COMMAND(Byte3);
	LCD_COMMAND(Byte4);
	LCD_COMMAND(Byte5);	
	LCD_COMMAND(LCD_CURSOROFF_BLINKOFF);
	return;
}

void LCD_ADDR(int address)
{
	LCD_COMMAND((1 << 7) | (char)address);
	return;
}

void LCD_Voltage(int x)
{
	char *bufferTh = NULL;
	char *bufferH = NULL;
	char *bufferT = NULL;
	char *bufferO = NULL;
	int Vref = 5;
	int Vin = 0;

	
	if(x<100)
	{
		Vin= x*Vref;
	}
	else
	{
		Vin = abs((x*Vref) - 100);
	}
		
		
	int thousands = Vin/1000;
	if(thousands >= 1)
	{
		Vin = Vin-1000*thousands;
	}

	itoa(thousands,bufferTh,10);
	LCD_STRING(bufferTh);
	LCD_STRING(".");
		
	int hundreds = Vin/100;
	if(hundreds >= 1)
	{
		Vin = Vin-100*hundreds;
	}
	itoa(hundreds,bufferH,10);
	LCD_STRING(bufferH);

	int tens = Vin/10;
	if(tens >= 1)
	{
		Vin = Vin-10*tens;
	}
	itoa(tens,bufferT,10);
	LCD_STRING(bufferT);
		
	int ones = Vin;
	itoa(ones,bufferO,10);
	LCD_STRING(bufferO);
}

void LCD_Integer(int x)
{
	char *bufferH = NULL;
	char *bufferT = NULL;
	char *bufferO = NULL;
		
	int thousands = x/1000;
	if(thousands >= 1)
	{
		x = x-1000*thousands;
	}
		
	int hundreds = x/100;
	if(hundreds >= 1)
	{
		x = x-100*hundreds;
	}
	itoa(hundreds,bufferH,10);
	LCD_STRING(bufferH);

	int tens = x/10;
	if(tens >= 1)
	{
		x = x-10*tens;
	}
	itoa(tens,bufferT,10);
	LCD_STRING(bufferT);
		
	int ones = x;
	itoa(ones,bufferO,10);
	LCD_STRING(bufferO);
}

void LCD_stepAngle(int count)
{
	int angle = (4* (count * 18)/10);

	if(angle >360)
	{
		angle = angle - 360;
	}

	LCD_Integer(angle);

	LCD_CHARACTER(0b11011111);

}

void clearRow(char row)
{
	if(row==0x13)
	{
		row = 0x00;
	}
	else if(row==0x53)
	{
		row = 0x40;
	}
	else if(row==0x27)
	{
		row = 0x14;
	}
	else if(row==0x67)
	{
		row = 0x54;
	}
		
	LCD_ADDR(row);
	LCD_STRING("                    ");
}

void scrollText2Position(char text[],char pos, char row)
{
	char* buffer = text;
	char printBuffer[20];
	int stringEnded = 0;
	int stringDelay = 10;

	int bufferPos = 0;
	int currentPos = row;

	while(1)
	{
		LCD_ADDR(currentPos);

		if(buffer[bufferPos]=='\0')
		{
			stringEnded = 1;
		}
		
		if(stringEnded ==0)
		{
			printBuffer[bufferPos]=text[bufferPos];
		}
		else
		{
			printBuffer[bufferPos]=' ';
		}


		if(bufferPos>20)
		{
			break;
		}
		else
		{
			bufferPos++;
		}
		
		for(int i=0;i<bufferPos;i++)
		{
			LCD_CHARACTER(printBuffer[i]);
		}

		currentPos--;
		_delay_ms(stringDelay);

		if(currentPos-pos == -1)
		{
			break;
		}
		
		clearRow(row);
		
	}
}


