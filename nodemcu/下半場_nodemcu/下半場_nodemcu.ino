#include <Servo.h>
#include <ESP8266WiFi.h>

#define CW   1650
#define STOP 1500
#define CCW  1350

Servo mgServo;
Servo ds04Servo1;
Servo ds04Servo2;

const int mgPin = 5; //D1
const int ds1Pin = 4; //D2
const int ds2Pin = 2; //D4

//arduino
const int stmotorPin1 = 0; //D3 -> arduino D2
const int stmotorPin2 = 14; //D5 -> arduino D7
const int _stmotorPin1 = 12; //D6 -> arduino D12
const int _stmotorPin2 = 13; //D7 -> arduino D13

const char* ssid = "WE_ARE_VENOM";
const char* password = "venomvenomweareweare";

WiFiServer wifiServer(2345);

void setup() {
  Serial.begin(115200);
  mgServo.attach(mgPin); //D1, pulse width (脈衝寬度修正)
  ds04Servo1.attach(ds1Pin);
  ds04Servo2.attach(ds2Pin);


  //step motor init
  pinMode(stmotorPin1, OUTPUT);
  pinMode(stmotorPin2, OUTPUT);
  pinMode(_stmotorPin1, OUTPUT);
  pinMode(_stmotorPin2, OUTPUT);

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

  mgServo.write(10);
  delay(100);
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

        // (1, 1)->clockwise; (1, 0)->reclockwise; (0, 0)->stop; 
        
        if (state == 1) {
          //GET (ds04 servo)
          ds04Servo1.writeMicroseconds(CCW);
          ds04Servo2.writeMicroseconds(CW);
          delay(1000);

        } else if (state == 2) {
          //RELEASE (ds04 servo)
          ds04Servo1.writeMicroseconds(CW);
          ds04Servo2.writeMicroseconds(CCW);
          delay(1000);

        } else if (state == 3) {
          //PULL (step motor)
          digitalWrite(stmotorPin1, HIGH);
          digitalWrite(stmotorPin2, HIGH);
          digitalWrite(_stmotorPin1, HIGH);
          digitalWrite(_stmotorPin2, HIGH);
          
        } else if (state == 4) {
          //PUT (step motor)
          digitalWrite(stmotorPin1, HIGH);
          digitalWrite(stmotorPin2, HIGH);
          digitalWrite(_stmotorPin1, LOW);
          digitalWrite(_stmotorPin2, LOW);
          
        } else if (state == 5) {
          Serial.println("in 5");
          mgServo.write(10);
          delay(300);
          
        } else if (state == 6) {
          Serial.println("in 6");
          mgServo.write(170);
          delay(300);
          
        } else if (state == 7) {
        
        } else if (state == 100) { //ds04 servo stop
          ds04Servo1.writeMicroseconds(STOP);
          ds04Servo2.writeMicroseconds(STOP);
          
        } else if (state == 101) { //mg servo stop
          
        } else if (state == 150) { //step motor stop
          digitalWrite(stmotorPin1, LOW);
          digitalWrite(stmotorPin2, LOW);
          digitalWrite(_stmotorPin1, LOW); 
          digitalWrite(_stmotorPin2, LOW);         
        }
        
        
      }
      client.flush();
    }

    Serial.println("Client disconnected");
  }
}
