// Launch a server, log progress to USB serial, change LED based on web input
// based on: https://diyprojects.io/esp8266-web-server-tutorial-create-html-interface-connected-object/
// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* SSID = "Actiontec-8318-2.4G"; 
const char* PASSWORD = "e3d9dd3c";

// Set web server port number to 80
WiFiServer server(80);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  while (!Serial) ;
  Serial.println("Hello world");

  // Connect to Wi-Fi network with SSID and PASSWORD
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address 
  Serial.print("\r\nWiFi connected at IP address:  ");
  Serial.println(WiFi.localIP());

  // Start Web Server
  server.begin();
}

// Main loop
void loop(){
  char *state = "ON</i>";
  // Create a client and listen for incoming clients
  WiFiClient client = server.available();   
  
  // Do nothing if server is not available
  if (!client) {
     return;
  }
  
  // Wait for a client 
  while(!client.available()){}
  
  // A new client is connected, get the request
  String request = client.readStringUntil('\r');
  Serial.print(request);
  client.flush();

  if (request.indexOf("/LED=ON") != -1) 
  {
    Serial.print("\t# switching LED on");
    digitalWrite(LED_BUILTIN, LOW);
    state = "ON</i>";
  } 
  else if (request.indexOf("/LED=OFF") != -1)
  {
    Serial.print("\t# switching LED off");
    digitalWrite(LED_BUILTIN, HIGH);
    state = "OFF</i>";
  }
  else if (request.indexOf("/favicon.ico") != -1)
  {
    client.println("HTTP/1.1 410 Gone");
    client.println("");
  }
  
  // Display GPIO status
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.print("<html><i>LED GPIO status: ");
  client.println(state); 
  client.println("<br><br>Switch GPIO state <a href=\"/LED=ON\"><b>ON</b></a> or <a href=\"/LED=OFF\"><b>OFF</b></a><br><img src=\"https://alselectro.files.wordpress.com/2018/04/d1_pinout.jpg\"></html>");
  Serial.println("");
}
