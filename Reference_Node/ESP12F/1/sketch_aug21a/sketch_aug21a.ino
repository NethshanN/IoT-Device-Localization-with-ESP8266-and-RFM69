
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char *ssid =  "Your wifi Network name";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Network password";
WiFiClient client;

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

unsigned long myChannelNumber = 1;
const char *myWriteAPIKey = "1GR99RDKT33TKGS0"; // ThingSpeak Write API key

const int ledPin =  LED_BUILTIN;// the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
float Value_1;
float Value_2;
long randNumber_1;
long randNumber_2;

String inString = "";    // string to hold input


void setup() 
{
  pinMode(ledPin, OUTPUT);   // Set LED pin as output
  Serial.begin(9600);        // Start serial communication
  delay(10);                 // Short delay for stabilization
  
  Serial.println("Connecting to ");  // Print WiFi connection status
  Serial.println(ssid);             // Print SSID

  WiFi.begin(ssid, pass);    // Start WiFi connection

  ThingSpeak.begin(client);  // Initialize ThingSpeak

  while (WiFi.status() != WL_CONNECTED)   // Wait for WiFi to connect
   {
    ledState = ~ledState;              // Toggle LED state
    digitalWrite(ledPin, ledState);    // Blink LED
    delay(500);                        // Wait for 500ms
    Serial.print(".");                 // Print progress dot
   }
  Serial.println("");           // New line after connection
  Serial.println("WiFi connected");  // Print WiFi connected message

  Serial.swap();               // Swap TX/RX pins for serial
}
 
void loop() 
{
  digitalWrite(ledPin, HIGH);  // Turn the LED on
  delay(1000);                 // Wait for 1 second
  digitalWrite(ledPin, LOW);   // Turn the LED off
  delay(1000);                 // Wait for 1 second
  
  if ((millis() - lastTime) > timerDelay)  // Check if it's time to execute the next cycle
  {
    Serial.println("#");
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED)   // Check and attempt to reconnect to WiFi if disconnected
    {
      Serial.print("Attempting to connect");
      WiFi.begin(ssid, pass);
      while(WiFi.status() != WL_CONNECTED)
      {
        ledState = ~ledState;
        digitalWrite(ledPin, ledState);
        delay(5000); 
        Serial.print("+");    
      } 
      delay(500); 
      Serial.println("\nConnected."); // Indicate successful connection
      ThingSpeak.begin(client);       // Initialize ThingSpeak
    }
    lastTime = millis();  // Update the last time marker
  }

  if (Serial.available() > 0) 
  {
      inString = Serial.readStringUntil('\n');  // Read the incoming string from Serial until a newline character
      
      // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
      // pieces of information in a channel.  
      ThingSpeak.setField(1, inString);  //Here, we write to field 1. 
      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // Send data to the ThingSpeak channel
  
      if(x == 200){  // checks if the HTTP response code is 200, which indicates the request was successful (standard HTTP success status)
        Serial.println("Channel update successful.");  // Confirm successful data upload
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x)); // Print error if upload fails
    }
      }
  
}
