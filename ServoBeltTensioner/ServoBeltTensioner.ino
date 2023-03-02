// Hack Wotever's BeltTensionner for hobby servos
// ---------------------- SETTINGS SECTION -----------------------------
#include <Servo.h>

// GLOBAL SETTINGS
Servo servo[2];
byte motor = 0;			// servo 0 or 1
int offset[2] = {63,65};	// max slack position

// ---------------------------------------------------------------------
void PrintLog(String message) {
	Serial.println("M" + String(motor) + ": " + message);
}

void setup() {
	Serial.begin(19200);
	servo[0].attach(PB8);
	servo[1].attach(PB9);
	while (!Serial)
	    delay(1);	// wait for native USB serial port to connect
	Serial.println("servos PB8, PB9 enabled");
	servo[0].write(offset[0]);
	servo[1].write(offset[1]);
}

void processCommand(String command) {
	if (command.startsWith("speed ")) {
		int speed = command.substring(6).toInt();

		if (0 > speed || 10000 < speed)
			PrintLog("invalid offset (should be >0 and <10000): "+String(speed));
		else {
			offset[motor] = (50 + command.substring(6).toInt())/100;
			PrintLog("offset set to "+String(offset[motor]));
		}
	}
	else {	// Position being an int from -32365 to +32365
		int value = (100 + command.substring(6).toInt())/200;

		if (0 > value)
			servo[motor].write(offset[motor]);	// no extra release for servos
		// hobby servos (even 270 degree ones) support values 0 to 180
		else servo[motor].write(offset[motor] + (81 + ((180 - offset[motor]) * value)) / 162);
	}
}

void loop() {
	if (Serial.available()) {
		char which = ' ', first = Serial.read();

		if('M' == first && ('1' == (which = Serial.read())
				    || '2' == which)) {
			Serial.read();	// discard blank
			motor = which - '1';
			processCommand(Serial.readStringUntil('\n'));
		}
		else Serial.println("Unsupported: "+first+which); 
	}
}
