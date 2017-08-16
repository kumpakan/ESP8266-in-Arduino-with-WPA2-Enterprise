/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

/*******************************************************************/
#include <ESP8266WiFi.h>
/*******************************************************************/
extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}
/*******************************************************************/
#define SERIAL_BAUD_RATE      115200
#define STARTUP_DELAY_MS      1000
/*******************************************************************/
// SSID to connect to
static const char* ssid = "Your_SSID";
// Username for authentification
static const char* username = "Your_Username";
// Password for authentification
static const char* password = "Your_Password";
/*******************************************************************/

//***** Wifi Personal *****
//const char* ssid = "your-ssid";
//const char* password = "your-password";
//***** Wifi Personal *****

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

const long interval = 5000;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(STARTUP_DELAY_MS);

  // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(STATION_MODE);

  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);

  wifi_station_set_config(&wifi_config);

  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  
  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));

  wifi_station_connect();

  // Wait for connection AND IP address from DHCP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Now we are connected
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
  Serial.println("Web Server started");

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
//***** Wifi Personal *****
// Connect to WiFi network
/*  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
*/
//***** Wifi Personal *****

  
}









void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long previousMillis = millis();
  while(!client.available()){
    //delay(1);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      //previousMillis = currentMillis;
      return;
    }
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(2, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

