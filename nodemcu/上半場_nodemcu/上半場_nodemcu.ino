#include <Servo.h>
#include <ESP8266WiFi.h>

Servo sgServo;
Servo mgServo;

const int sgPin = 5; //D1

const char* ssid = "WE_ARE_VENOM";
const char* password = "venomvenomweareweare";

WiFiServer wifiServer(2345);

void setup() {
  Serial.begin(9600);
  sgServo.attach(sgPin);

  //waiting for wifi connected
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting..");
  }

  Serial.print("Conntected to Wifi. IP:");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
  Serial.println("port 2345 opened");

  Serial.println(WiFi.macAddress());

  mgServo.write(0);
  delay(500);
}

void loop() {
  WiFiClient client = wifiServer.available();

  if (client) {

    while (client.connected()) {
      
      while (client.available()) {
        
        String req = client.readStringUntil('\r');
        req.trim();
        int state = req.toInt();
        Serial.println(state);
        
        if (state == 1) {
          //GET (ev3 motor)
          
        } else if (state == 2) {
          //RELEASE (ev3 motor)

        } else if (state == 3) {
          // sgServo up
          sgServo.write(0);
          
          
        } else if (state == 4) {
          // sgServo down
          sgServo.write(90);

          
        } else if (state == 5) {
          // mgServo up

          
        } else if (state == 6) {
          // mgServo down

          
        } else if (state == 7) {
        
        } else if (state == 100) { //ev3 motor stop
          
        } else if (state == 101) { //mg servo stop
          
        } else if (state == 150) { //sg servo stop
      
        }
        
        
      }
      client.flush();
    }

    Serial.println("Client disconnected");
  }
}
