/*
 * Autobot
 * 
 * Code moves a robot and uses a SR04 sensor to detect objects
 * All Serial.print statements are used to troubleshoot and can be removed if desired
 * 
 */

//Motor A
const int PWMA = 3;   //Speed control pin
const int AIN1 = 8;   //Direction - HIGH or LOW
const int AIN2 = 9;   //Direction - HIGH or LOW

//MotorB
const int PWMB = 5;
const int BIN1 = 12;
const int BIN2 = 13;

//NodeMCU 
const int motorA = 6;
const int motorB = 7; 

const int motorA_direct = 10;
const int motorB_direct = 11;

int mtA_state = 0;
int mtB_state = 0;

int mtA_direct = 0;
int mtB_direct = 0;


/* Motor speed control
 *  
 *    mtrSpeed - The normal forward speed
 *    turnSpeed - used to turn the robot by making one motor turn faster than the other
 *
 */
int mtrSpeed = 255;     //regular robot speed
int turnSpeed = 200;    //faster speed used to turn robot


void setup(){
      Serial.begin(9600);           //Setup Serial monitor for 9600 baud

      pinMode(PWMA, OUTPUT);        //Motor A
      pinMode(AIN1, OUTPUT);
      pinMode(AIN2, OUTPUT);

      pinMode(PWMB, OUTPUT);       //Motor B
      pinMode(BIN1, OUTPUT);
      pinMode(BIN2, OUTPUT);

      pinMode(motorA, INPUT);
      pinMode(motorB, INPUT);

      pinMode(motorA_direct, INPUT);
      pinMode(motorB_direct, INPUT);
 
      Serial.println("start move");
}


/*
 * Main Program Loop
 */
 
void loop() {
  mtA_state = digitalRead(motorA);
  mtB_state = digitalRead(motorB);
  
  mtA_direct = digitalRead(motorA_direct);
  mtB_direct = digitalRead(motorB_direct);

  Serial.println(mtA_direct);

  if (mtA_state == LOW){
    move(1, 0, 0);
  } else if (mtA_state == HIGH && mtA_direct == HIGH){ 
    move(1, 180, 1);
  } else if (mtA_state == HIGH && mtA_direct == LOW){
    move(1, 100, 0);
  }

  if (mtB_state == LOW){
    move(2, 0, 0);
  } else if (mtB_state == HIGH && mtB_direct == HIGH){
    move(2, mtrSpeed, 1);
  } else if (mtB_state == HIGH && mtB_direct == LOW){
    move(2, mtrSpeed, 0);
  }
  
}


/*
 * Move motor logic
 */
void move(int motor, int speed, int direction) {

/*Move specific motor at speed and direction
*     motor: 1 for Motor A, 2 for motor B
*     speed: 0 is off, and 255 is full speed
*     direction: 0 clockwise, 1 counter-clockwise
*/

      boolean inPin1 = LOW;
      boolean inPin2 = HIGH;

      if(direction == 1){
            inPin1 = HIGH;
            inPin2 = LOW;
      }

      if(motor == 1) {
            digitalWrite(AIN1, inPin1);         //Used to detremine motor direction
            digitalWrite(AIN2, inPin2);         //Used to detremine motor direction
            analogWrite(PWMA, speed); 
      } else if (motor == 2){
        digitalWrite(BIN1, inPin1);
        digitalWrite(BIN2, inPin2);
        analogWrite(PWMB, speed);
      }
}
