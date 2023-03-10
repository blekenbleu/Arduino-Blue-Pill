#include <Servo.h>
// echo Serial bytes in HEX; use PWM to control LED feedback
// https://blekenbleu.github.io/Arduino/

#define LED PC13		// Blue Pill green LED

int next = LOW;
void setup() {			// setup() code runs once
  // initialize as an output digital pin connected to green LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);	// turn off LED by floating pin HIGH

  // Initialize serial and wait for port to be opened:
  Serial.begin(9600);
  while (!Serial)
    delay(1);			// wait for native USB serial port to connect
  Serial.println("Blue_ASCII_PWM_LED: connected");
  digitalWrite(LED, next);
}

// loop() is not REALLY a loop;
// it is just the main routine, which gets called often.
byte received;
bool got = false;
void loop() {
  // main code goes here, to be called repeatedly:
  while (0 < Serial.available()) {
    received = Serial.read();
    Serial.print(received, HEX);
	delay(1);
    got = true;
  }
  if (got) {
	next = (HIGH == next) ? LOW : HIGH;
	digitalWrite(LED, next);
  	Serial.write("\n");
	got = false;
  }
}
