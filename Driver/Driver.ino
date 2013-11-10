/* Motor Driver for RC Cars
 * For RC devices using PWM signals
 * This takes a instructions
 *
 * S for Steering
 * the packet expected is
 * "S100\n" to "S-100\n" this means 100% sterring where 100% is left and -100 is right  
 *
 * M is for Motor 
 * We expect "M100\n" to "M-100\n"
 * 100% speed to -100% We assume that at 0% we are stopped. This might be different for some
 * RC cars
 *
 * H is for heartbeat. 
 * We send a H every 1 second otherwise it will defult to 0 and stop the motor. 
 *
 */



#include <Servo.h> 

#define FREQ 50
#define MIN_PULSE 1000
#define MAX_PULSE 2000
#define PWM_RANGE (MAX_PULSE - MIN_PULSE)

Servo motor;
Servo steer;
bool invalid = false;
char mode;
String dataIn = "";

char intBuffer[12];

void setup() 
{ 
	motor.attach(9,MIN_PULSE,MAX_PULSE);
	steer.attach(10,MIN_PULSE,MAX_PULSE);
	Serial.begin(115200);
	Serial.println("Ready");

} 

void loop() {

	while ( Serial.available()) {
		char ch = Serial.read();

		if (ch == 'M' && dataIn == "")
		{
			mode = 'M';
		}
		else if (ch == 'S' && dataIn == "")
		{
			mode = 'S';
		}
		else if (ch == 'H' && dataIn == "")
		{
			mode = 'H';
		}
		else if (ch == '\n')
		{
			if (mode == 'H') 
			{
				Serial.println("HeartBeat");
				//exeHeartbeat
				dataIn = "";
			}
			else 
			{
				int intLength = dataIn.length() + 1;
				dataIn.toCharArray(intBuffer, intLength);
				int percent = atoi(intBuffer);
				if ( !(percent <= 100 && percent >= -100)) 
				{
					invalid = true;
				}

				if (!invalid) 
				{
					Serial.print("Percent print: ");
					Serial.println(percent);
					exeCommand(mode, percent);
				}
				else 
				{
					Serial.println("Invalid Command\n");
				}
				dataIn = "";
				invalid = false;
			}
		}
		else 
		{
			if ( (int)ch >= 48 && (int)ch <= 57)
			{
				dataIn += ch;
			}
			else 
			{
				invalid = true;
			}
		}
	}
}

void exeCommand(char mode, int percent) {
	if (mode == 'M')
	{
		motor.writeMicroseconds(calc_duty(percent));
	}
	else if (mode == 'S')
	{
		steer.writeMicroseconds(calc_duty(percent));
	}
}
/*
void exeHeartbeat () {
unsigned long previousMillis = 0; // last time update
long interval = 2000; // interval at which to do something (milliseconds)

void setup(){
}

void loop(){
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
     previousMillis = currentMillis;  

     // do something
  }
}


}
*/
int calc_duty (int percent_cycle)
{
	float pulse = 0;
	float percent = abs(percent_cycle);
	if (percent_cycle >= 0 )
	{
		pulse = MIN_PULSE + (PWM_RANGE/2) + ((PWM_RANGE/2) * (percent / 100));
	}
	else 
	{
		pulse = MIN_PULSE + (PWM_RANGE/2) - ((PWM_RANGE/2) * (percent / 100));
	}
	Serial.print("Pulse width: ");
	Serial.println(pulse);

	return (int) pulse;
}

