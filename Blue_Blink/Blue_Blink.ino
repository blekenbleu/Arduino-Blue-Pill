void setup() {
  // put Blue Pill setup code here, to run once:
  // initialize as an output digital pin PC13, connected to green LED
  pinMode(PC13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (PC13, HIGH); // turn the LED off by letting PC13 go HIGH
  delay(500);                // wait a half-second
  digitalWrite (PC13, LOW);  // turn the LED on by pulling PC13 LOW
  delay(1000);               // wait for a second
}
