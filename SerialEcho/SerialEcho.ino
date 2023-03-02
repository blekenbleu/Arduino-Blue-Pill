/*
  SerialEcho sketch

  Any text you type in the IDE Serial monitor will be written back out that serial port

  This works on ESP8266 D1 UNO R1
  https://www.instructables.com/Arduino-WeMos-D1-WiFi-UNO-ESP-8266-IoT-IDE-Compati/
  June 10, 2021
*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Hello world from SerialEcho");
}

void loop() {
  while (Serial.available()) {      // If anything comes in Serial (USB)
    digitalWrite(LED_BUILTIN, LOW);
    Serial.write(Serial.read());   // read it and send it back
  }
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by floating pin out 
}
