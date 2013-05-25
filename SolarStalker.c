#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <math.h>

#include "PORT_ASSIGNMENTS.h"
#include "LCD_MENU.h"
#include "AD.h"
#include "STEPPER.h"
#include "LCD.h"

void checkButtons(void);
void updateLCD(void);
void checkMode(void);
void PANEL_init(void);
int checkCable(void);
void checkBackLight(void);
void checkSwitches(void);

int main(void)
{
	PORT_init();
	AD_init();
	_delay_ms(200);
	LCD_init();
	
	scrollText2Position("Solar Stalker",0x04,0x13);
	scrollText2Position("Senior Design",0x44,0x53);
	_delay_ms(500);

	//Checks to see if cable is connected
	while(checkCable())
	{
		LCD_ADDR(0x00);
		LCD_STRING("Please Insert Cable");		
	}

	//Displays the first menu option
	LCD_COMMAND(LCD_CLEAR_HOME);
	LCD_ADDR(0x00);
	LCD_STRING("    Solar Stalker");
	LCD_ADDR(0x14);
	LCD_STRING("->");
	LCD_STRING(mainScreen[mainScreenLine[0]]);
	LCD_ADDR(0x54);
	LCD_STRING(mainScreen[mainScreenLine[1]]);
	
	while(1)
	{
		checkBackLight();
		checkButtons();
		checkMode();

		if(checkCable())
		{
			LCD_COMMAND(LCD_CLEAR_HOME);

			while(checkCable())
			{
				LCD_ADDR(0x00);
				LCD_STRING("Please Insert Cable");
			}
			updateScreen=1;
		}
		updateLCD();
		
	}
}

void checkButtons(void)
{

	//FOWARD_ENTER BUTTON
	if((BUTTON_VALUE & 0x01) == 0x01)
	{
		backLightCount = 0;
		backLight=1;
		checkBackLight();

		while((BUTTON_VALUE & 0x01) == 0x01){}

		//If on MainScreen, see which option is selected and goto that option
		if(mainScreenView==1)
		{
			if(mainScreenLineSelected ==0)	//Goto option1, passive mode
			{
				mainScreenView =0;
				option1View =1;
				option1Line =0;
				
				passiveMode = 1;

				updateScreen =1;
			}
			else if(mainScreenLineSelected ==1)	//Goto option2, manual mode
			{
				mainScreenView =0;
				option2View =1;
				option2Line =0;

				manualMode = 1;

				updateScreen =1;
			}
			else if(mainScreenLineSelected ==2)
			{
				mainScreenView =0;
				option3View =1;
				option3Line =0;

				demoMode = 1;

				updateScreen =1;
			}			
		}

		else if(option1View==1)
		{
			
		}
			
		//If on Option2 Screen, return to main screen
		else if(option2View==1)
		{
			
		}

		else if(option3View==1)
		{

		}
	}

	//UP BUTTON
	else if((BUTTON_VALUE & 0x02) == 0x02)
	{
		backLightCount = 0;
		backLight=1;
		checkBackLight();

		while((BUTTON_VALUE & 0x02) == 0x02)
		{
			if(option2View==1)
			{
				stepper_oneStepLeft();
			}
		}

		if(mainScreenView==1)
		{
			
			if(mainScreenLine[0]==0 && mainScreenLineSelected==0)
			{

			}
			else if(mainScreenLine[0]==mainScreenLineSelected)
			{
				mainScreenLineSelected--;
				mainScreenLine[0]--;
				mainScreenLine[1]--;
				updateScreen = 1;
			}
			else
			{
				mainScreenLineSelected--;
				updateScreen = 1;
			}
		}
		else if(option1View==1)
		{
				
		}
			
		else if(option2View==1)
		{
			stepper_oneStepLeft();
		}
		else if(option3View==1)
		{
				
		}
	}

	//DOWN BUTTON
	else if((BUTTON_VALUE & 0x04) == 0x04)
	{
		backLightCount = 0;
		backLight=1;
		checkBackLight();

		while((BUTTON_VALUE & 0x04) == 0x04)
		{
			if(option2View==1)
			{
				stepper_oneStepRight();
			}
		}

		if(mainScreenView==1)
		{
			if(mainScreenLine[1]==2 && mainScreenLineSelected==2)
			{

			}
			else if(mainScreenLine[1]==mainScreenLineSelected)
			{
				mainScreenLineSelected++;
				mainScreenLine[0]++;
				mainScreenLine[1]++;
				updateScreen = 1;
			}
			else
			{
				mainScreenLineSelected++;
				updateScreen = 1;
			}	
		}

		else if(option1View==1)
		{
				
		}		
		else if(option2View==1)
		{
			stepper_oneStepRight();
		}
		else if(option3View==1)
		{
				
		}	
	}

	//BACK BUTTON
	else if((BUTTON_VALUE & 0x08) == 0x08)
	{
		backLightCount = 0;
		backLight=1;
		checkBackLight();

		while((BUTTON_VALUE & 0x08) == 0x08){}

		if(mainScreenView==1)
		{
			
		}
		//If on Option1 Screen, return to main screen
		else if(option1View==1)
		{
			mainScreenView =1;
			option1View =0;
			option1Line =0;
			
			passiveMode = 0;

			updateScreen =1;	
		}
		//If on Option2 Screen, return to main screen
		else if(option2View==1)
		{
			mainScreenView =1;
			option2View =0;
			option2Line =0;

			manualMode = 0;

			updateScreen =1;
		}
		else if(option3View==1)
		{
			mainScreenView =1;
			option3View =0;
			option3Line =0;

			demoMode = 0;

			updateScreen =1;
		}
	}
}

void updateLCD(void)
{
	if(updateScreen ==1)
	{	
		if(mainScreenView==1)
		{
			LCD_COMMAND(LCD_CLEAR_HOME);
			LCD_ADDR(0x00);
			LCD_STRING("    Solar Stalker");
			if(mainScreenLineSelected==mainScreenLine[0])
			{
				LCD_ADDR(0x14);	
				LCD_STRING("->");
				LCD_STRING(mainScreen[mainScreenLine[0]]);
				LCD_ADDR(0x54);
				LCD_STRING(mainScreen[mainScreenLine[1]]);
			}
			if(mainScreenLineSelected==mainScreenLine[1])
			{
				LCD_ADDR(0x14);
				LCD_STRING(mainScreen[mainScreenLine[0]]);
				LCD_ADDR(0x54);
				LCD_STRING("->");
				LCD_STRING(mainScreen[mainScreenLine[1]]);
			}
	
		}
		if(option1View==1)
		{
			LCD_COMMAND(LCD_CLEAR_HOME);
			LCD_STRING(option1Screen[option1Line]);
		}
		if(option2View==1)
		{
			LCD_COMMAND(LCD_CLEAR_HOME);
			LCD_STRING(option2Screen[option2Line]);
		}
		if(option3View==1)
		{
			LCD_COMMAND(LCD_CLEAR_HOME);
			LCD_STRING(option3Screen[option3Line]);
		}
	}

	if((option1View==1) |(option1View==2)|(option1View==3))
	{
		LCD_ADDR(0x54);
		LCD_STRING("A:");
		LCD_Voltage(AD0);
		LCD_STRING("v");
		LCD_STRING(" B:");
		LCD_Voltage(AD1);
		LCD_STRING("v");
	}

	updateScreen = 0;
}

void checkMode(void)
{
	if(passiveMode==1)
	{
		AD_getValues();

		for(int i=0;i<100;i++)
		{		
			_delay_ms(50);
			AD_getValues();
			updateLCD();

			if((BUTTON_VALUE & 0x08) == 0x08)
			{
				return;
			}
		}
		
		for(int i=0;i<10;i++)
		{
			AD_getValues();
			//Compares sensors to see which AD value was higher, then moves motor
			if(AD0> AD1)
			{
				if((AD0-AD1)<10)
				{
					MOTOR_PORT = MOTOR_PORT & 0x0F;
				}
				else
				{
					stepper_oneStepLeft();
				}
			}
			else
			{
				if((AD1-AD0)<10)
				{
					MOTOR_PORT = MOTOR_PORT & 0x0F;
				}
				else
				{
					stepper_oneStepRight();
				}
			}

			MOTOR_PORT = MOTOR_PORT & 0x0F;
		}

	}
	else if(demoMode==1)
	{
		AD_getValues();

		//Compares sensors to see which AD value was higher, then moves motor
		if(AD0> AD1)
		{
			if((AD0-AD1)<150)
			{
				MOTOR_PORT = MOTOR_PORT & 0x0F;
			}
		else
			stepper_oneStepLeft();
		}
		else
		{
			if((AD1-AD0)<150)
			{
				MOTOR_PORT = MOTOR_PORT & 0x0F;
			}
		else
			stepper_oneStepRight();
		}
	}
	else if(manualMode==1)
	{
		AD_getValues();
	}

	if((BUTTON_VALUE & 0x30) == 0x20)
	{
		BUTTON_PORT = BUTTON_PORT | 0b01000000;
			
		if((passiveMode==1) | (demoMode==1))
		{
			while((BUTTON_VALUE & 0x30) != 0x10)
			{
				_delay_ms(2000);
				stepper_oneStepLeft();
			}

			while((AD0 < 500) & (AD1 < 500))
			{
				AD_getValues();
				_delay_ms(50);
				updateLCD();

				if((BUTTON_VALUE & 0x04) == 0x04)
					break;
			}

			_delay_ms(500);
			stepper_oneStepRight();
			_delay_ms(500);
			stepper_oneStepRight();
			_delay_ms(500);
			stepper_oneStepRight();
			_delay_ms(500);
			stepper_oneStepRight();
			_delay_ms(500);
			stepper_oneStepRight();
			
			

		}
	}

	if((BUTTON_VALUE & 0x30) == 0x10)
	{
		BUTTON_PORT = BUTTON_PORT | 0b01000000;
			
		if((passiveMode==1) | (demoMode==1))
		{
			while((BUTTON_VALUE & 0x30) != 0x20)
			{
				_delay_ms(2000);
				stepper_oneStepRight();
			}

			while((AD0 < 500) & (AD1 < 500))
			{
				AD_getValues();
				updateLCD();

				if((BUTTON_VALUE & 0x04) == 0x04)
					break;
			}

			_delay_ms(500);
			stepper_oneStepLeft();
			_delay_ms(500);
			stepper_oneStepLeft();
			_delay_ms(500);
			stepper_oneStepLeft();
			_delay_ms(500);
			stepper_oneStepLeft();
			_delay_ms(500);
			stepper_oneStepLeft();
			
		}
	}
}

int checkCable(void)
{
	if((BUTTON_VALUE & 0x30) == 0x00)
	{
		return 1;
	}
	else
		return 0;
}

void checkBackLight(void)
{
	if(backLight)
	{
		BUTTON_PORT = BUTTON_PORT & 0b00111111;

		if(backLightCount<200000)
		{
			backLightCount++;
		}
		else
		{
			backLightCount = 0;
			backLight=0;
		}
	}
	else
	{
		BUTTON_PORT = BUTTON_PORT | 0b01000000;
	}
}																																
