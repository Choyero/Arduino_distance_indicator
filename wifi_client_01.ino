#include <ESP8266WiFi.h>

const char* ssid = "your wifi network";           // SSID of your home WiFi
const char* password = "your wifi password";            // password of your home WiFi
int GreenLED = 15;
int YellowLED = 13;
int RedLED = 12;
int flashing = 0;


IPAddress server(192,168,0,4);       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(9600);              
  WiFi.begin(ssid, password);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 Serial.println("Connected to wifi");
  Serial.print("IP: ");     
  Serial.println(WiFi.localIP());
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
}

void loop () {
  client.connect(server, 80);   // Connection to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  if (answer == "greenON"){
    digitalWrite(GreenLED, HIGH);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, LOW);
    flashing = 0;
  }
  else if (answer == "yellowON") {
    digitalWrite(GreenLED, LOW);
    digitalWrite(YellowLED, HIGH);
    digitalWrite(RedLED, LOW);
    flashing = 0;
  }
  else if (answer == "redON") {
    digitalWrite(GreenLED, LOW);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, HIGH);
    flashing = 0;
  }
  else if (answer == "redFLASH") {
    flashing = 1;
    digitalWrite(GreenLED, LOW);
    digitalWrite(YellowLED, LOW);
    digitalWrite(RedLED, LOW);
  }
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
  client.flush();
}
