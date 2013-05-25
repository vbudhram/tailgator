int motorCount = 0;
int stepperDelay = 100;
int motorState0C=1;
int motorState06=0;
int motorState03=0;
int motorState09=0;

void updateLCD(void);
void stepper_oneStepRight(void);
void stepper_oneStepLeft(void);

void stepper_oneStepRight(void)
{	
	if(motorState09==1)
	{
		motorState0C=1;
		motorState06=0;
		motorState03=0;
		motorState09=0;

		MOTOR_PORT = 0x3C;
    	_delay_ms(stepperDelay);
	}
	else if(motorState0C==1)
	{
		motorState0C=0;
		motorState06=1;
		motorState03=0;
		motorState09=0;

		MOTOR_PORT = 0x36;
    	_delay_ms(stepperDelay);
	}
	else if(motorState06==1)
	{
		motorState0C=0;
		motorState06=0;
		motorState03=1;
		motorState09=0;

		MOTOR_PORT = 0x33;
		_delay_ms(stepperDelay);
	}
	else if(motorState03==1)
	{
		motorState0C=0;
		motorState06=0;
		motorState03=0;
		motorState09=1;

		MOTOR_PORT = 0x39;
		_delay_ms(stepperDelay);
	}

	MOTOR_PORT = MOTOR_PORT & 0x0F;

	updateLCD();

	if(motorCount>=50)
		motorCount = 50;
	else
		motorCount++;

}

void stepper_oneStepLeft(void)
{
	if(motorState0C==1)
	{
		motorState0C=0;
		motorState06=0;
		motorState03=0;
		motorState09=1;

		MOTOR_PORT = 0x39;
    	_delay_ms(stepperDelay);
	}
	else if(motorState09==1)
	{
		motorState0C=0;
		motorState06=0;
		motorState03=1;
		motorState09=0;

		MOTOR_PORT = 0x33;
    	_delay_ms(stepperDelay);
	}
	else if(motorState03==1)
	{
		motorState0C=0;
		motorState06=1;
		motorState03=0;
		motorState09=0;

		MOTOR_PORT = 0x36;
		_delay_ms(stepperDelay);
	}
	else if(motorState06==1)
	{
		motorState0C=1;
		motorState06=0;
		motorState03=0;
		motorState09=0;

		MOTOR_PORT = 0x3C;
		_delay_ms(stepperDelay);
	}

	MOTOR_PORT = MOTOR_PORT & 0x0F;

	updateLCD();

	if(motorCount<=0)
		motorCount = 0;
	else
		motorCount--;

}
