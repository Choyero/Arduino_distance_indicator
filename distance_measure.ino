#include <ESP8266WiFi.h>

int GreenLED = 15;
int RedLED = 13;
int YellowLED = 5; 
int Echo = 12;
int Trig = 14;
long duration;
int distance;
int flashing = 0;

const char* ssid = "your network";
const char* password = "your password";

WiFiServer server(80);


void setup() {
  // put your setup code here, to run once:
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  Serial.begin(9600);
   // Connect to Wifi Network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

 Serial.println("\n");
 Serial.println("connected to ");
 Serial.println(ssid);
 //Start server
 server.begin();
 Serial.println("Server has started");
 //Print IP
 Serial.println("Server can be reached at: ");
 Serial.println("http://");
 Serial.println(WiFi.localIP());
 Serial.println("/");

}

void loop() {
  // put your main code here, to run repeatedly:

  
  // Check to see if client connection
 WiFiClient client = server.available();
 if (!client) {
   return;
 }


 Serial.println("new client connected");


   if (flashing == 1) {
    digitalWrite(RedLED, HIGH);
    delay(800);
    digitalWrite(RedLED, LOW);
    delay(300);
    digitalWrite(RedLED, HIGH);
    delay(800);
    digitalWrite(RedLED, LOW);
    delay(300);
    digitalWrite(RedLED, HIGH);
    delay(800);
    digitalWrite(RedLED, LOW);
    delay(300);
  }
  
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);

  distance = duration * 0.034/2;
  if (distance >= 100 ) { //far away still
    digitalWrite(GreenLED, HIGH);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, LOW);
    flashing = 0;
    client.println("greenON\r"); // tell client to turn on its green led. 
  } 
  else if (distance > 60 && distance < 100) { //getting close but still not there
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, LOW);
    digitalWrite(YellowLED, HIGH);
    flashing = 0;
    client.println("yellowON\r"); // tell client to turn on its yellow led.
  }
  else if (distance > 40 && distance <= 60) { // good distance 
    digitalWrite(GreenLED, LOW);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, HIGH);
    flashing = 0;
    client.println("redON\r"); // tell clien to turn on its yellow led.
  }
  else if (distance <= 40) { // too close back up;
    digitalWrite(GreenLED, LOW);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, LOW);
    flashing = 1;
    client.println("redFLASH\r");
  }

delay(1);
 Serial.println("Client disconnected");
 Serial.println("");
  
}
