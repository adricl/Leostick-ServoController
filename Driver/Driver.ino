#include <Servo.h> 

#define NANO => 1000000000;
#define DUTY_TOP => 10;
#define DUTY_BOT => 5.5;

#define PWM_RANGE => DUTY_TOP - DUTY_BOT;
#define FREQ => 50;

Servo motor;
Servo steer;
String dataIn[30];
char mode;
void setup() 
{ 
	motor.attach(9);
	steer.attach(10);
	Serial.begin(19200);
	Serial.println("Ready");
} 

void loop() {
  
	if ( Serial.available()) {
		char ch = Serial.read();
		if (ch == 'M' && dataIn.length == 0)
		{
			mode = 'M';
		}
		else if (ch == 'S' && dataIn.length == 0)
		{
			mode = 'S';
		}
		else if (ch == 'H' && dataIn.length == 0)
		{
			mode = 'H';
		}
		else if (ch == '\n')
		{
			Serial.print(dataIn);
			exeCommand();
			dataIn = "";
		}
		else 
		{
			dataIn += ch;
		}
		
		


	}
}

void exeCommand() {
	if (mode == 'M')
	{

	}
}


int calc_duty (float percent_duty)
{
	my ($duty, $period, $percent_scale)  = (0,0,0);
	
	$period = ( 1 / FREQ ) * NANO;
	if ($percent_duty >= 0 )
	{
		$duty = DUTY_BOT + PWM_RANGE/2 + (PWM_RANGE/2) * (abs($percent_duty) / 100);
	}
	else 
	{
		$duty = DUTY_BOT + PWM_RANGE/2 - (PWM_RANGE/2) * (abs($percent_duty) / 100);
	}
	print $duty . "\n";	
	$duty = $period - $period * ($duty/100);
	return $duty
}
