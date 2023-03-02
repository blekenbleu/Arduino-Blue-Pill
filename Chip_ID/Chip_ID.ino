/* 
 *  Get Chip ID
 *  https://cyaninfinite.com/getting-started-with-the-wemos-d1-esp8266-wifi-board/
 */

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("");
  Serial.println("");
  Serial.println("Check ID in:");
  Serial.println("https://www.wemos.cc/verify_products");
  Serial.printf("Chip ID = %08Xn", ESP.getChipId());
  Serial.println("");
  Serial.println("");
  delay(5000);
}
