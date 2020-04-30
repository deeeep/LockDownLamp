  
/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32
31.01.2017 by Jan Hendrik Berlin

adapted for 4 LEDs ESP32 Velleman
13.04.2020 by Deepak Mehta and David Truyens
 
 */
#include <WiFi.h>
#include <ESPmDNS.h>

const char* ssid     = "Deeeep's Wifi";
const char* password = "deepakmehta";

WiFiServer server(80);

int LED1pin = 13;
int LED2pin = 12;
int LED3pin = 27;
int LED4pin = 33;

void setup()
{
    Serial.begin(115200);
    
    pinMode(LED1pin, OUTPUT);      // set the LED pin mode
    pinMode(LED2pin, OUTPUT);      // set the LED pin mode
    pinMode(LED3pin, OUTPUT);      // set the LED pin mode
    pinMode(LED4pin, OUTPUT);      // set the LED pin mode
  
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
   
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
    }
    server.begin();
}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H1\">here</a> Lampje1 aan.<br>");
            client.print("Click <a href=\"/L1\">here</a> Lampje1 uit.<br>");
            client.print("Click <a href=\"/H2\">here</a> Lampje2 aan.<br>");
            client.print("Click <a href=\"/L2\">here</a> Lampje2 uit.<br>");
            client.print("Click <a href=\"/H3\">here</a> Lampje3 aan.<br>");
            client.print("Click <a href=\"/L3\">here</a> Lampje3 uit.<br>");
            client.print("Click <a href=\"/H4\">here</a> Lampje4 aan.<br>");
            client.print("Click <a href=\"/L4\">here</a> Lampje4 uit.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H1")) {
          digitalWrite(LED1pin, HIGH);               // GET /H1 turns the LED1 on
        }
        if (currentLine.endsWith("GET /L1")) {
          digitalWrite(LED1pin, LOW);                // GET /L1 turns the LED1 off
        }
        if (currentLine.endsWith("GET /H2")) {
          digitalWrite(LED2pin, HIGH);               // GET /H2 turns the LED2 on
        }
        if (currentLine.endsWith("GET /L2")) {
          digitalWrite(LED2pin, LOW);                // GET /L2 turns the LED2 off
        }
        if (currentLine.endsWith("GET /H3")) {
          digitalWrite(LED3pin, HIGH);               // GET /H3 turns the LED3 on
        }
        if (currentLine.endsWith("GET /L3")) {
          digitalWrite(LED3pin, LOW);                // GET /L3 turns the LED3 off
        }
        if (currentLine.endsWith("GET /H4")) {
          digitalWrite(LED4pin, HIGH);               // GET /H4 turns the LED4 on
        }
        if (currentLine.endsWith("GET /L4")) {
          digitalWrite(LED4pin, LOW);                // GET /L4 turns the LED4 off
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
