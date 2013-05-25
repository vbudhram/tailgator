#include <avr/interrupt.h>

unsigned int AD0 = 0; // AD channel A value
unsigned int AD1 = 0; // AD channel B value
int ADcount = 0;

void AD_init(void)
{
	// Set ADC presc- 125KHz sample rate @ 16MHz
	ADCSRA |= (1<<ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	ADMUX =(0<<REFS1)|(1<<REFS0)|0;
	ADMUX |=(0<<ADLAR); //left adjust ADC-8 bit reading

	//Auto Triggering of the ADC is enabled.
	ADCSRA |= (1 << ADATE);

	ADCSRA |= (1 << ADEN); //Bit 7 ADEN: ADC Enable
	ADCSRA |= (1 << ADSC); // Start A2D Conversions
}

void AD_getValues(void)
{
	if(ADcount==0)
	{
		AD0 = ADC;
		ADcount++;
		ADMUX = 0b01000001;
	}
	else if(ADcount==1)
	{
		AD1 = ADC;
		ADcount=0;
		ADMUX = 0b01000000;
	}
}
