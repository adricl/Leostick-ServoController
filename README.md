Leostick-ServoController
========================

Simple code to controll motor controllers using pwm. Takes in serial commands and has a heartbeat.

Motor Driver for RC Cars
For RC devices using PWM signals
This takes a instructions

S for Steering
the packet expected is
"S100\n" to "S-100\n" this means 100% sterring where 100% is left and -100 is right  

M is for Motor 
We expect "M100\n" to "M-100\n"
100% speed to -100% We assume that at 0% we are stopped. This might be different for some
RC cars

H is for heartbeat. 
We send a H every 1 second otherwise it will defult to 0 and stop the motor. 

