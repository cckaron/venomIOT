int apin=8;
int bpin=9;
int cpin=10;
int dpin=11;
int delaytime=3;

void setup() {
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  pinMode(dpin, OUTPUT);
}

void loop() {
  digitalWrite(dpin, HIGH);
  delay(delaytime);
  digitalWrite(dpin, LOW);
  digitalWrite(cpin, HIGH);
  delay(delaytime);
  digitalWrite(cpin, LOW);
  digitalWrite(bpin, HIGH);
  delay(delaytime);
  digitalWrite(bpin, LOW);
  digitalWrite(apin, HIGH);
  delay(delaytime);
  digitalWrite(apin, LOW);
}
