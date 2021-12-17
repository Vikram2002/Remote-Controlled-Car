// H-Bridge motor driver pins
#define    L_CTRL1   2
#define    L_CTRL2   4
#define    L_PWM     5

#define    R_CTRL1   7
#define    R_CTRL2   8
#define    R_PWM     6

#include <Servo.h>

Servo myservo;
Servo myservo2;  // create servo object to control a servo

const int trigPin = A5;
const int echoPin = A4;

long duration;
int distance;

int inc = 90;
int inc2 = 90;


void setup() {
  myservo.attach(3);
  myservo2.attach(10);

  Serial.begin(9600);

  myservo.write(inc);
  myservo2.write(inc2);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void leftMotor(int motorPower)
{
    motorPower = constrain(motorPower, -255, 255);   // constrain motorPower to -255 to +255
    if(motorPower >= 0)
    {
        // spin CW
        digitalWrite(L_CTRL1, HIGH);
        digitalWrite(L_CTRL2, LOW);
        analogWrite(L_PWM, abs(motorPower));
    }
    else
    {
        // spin CCW
        digitalWrite(L_CTRL1, LOW);
        digitalWrite(L_CTRL2, HIGH);
        analogWrite(L_PWM, abs(motorPower));
    }
}

/*******************************************************************************/
void leftBrake()
{
    // setting both controls HIGH, shorts the motor out -- causing it to self brake.
    digitalWrite(L_CTRL1, HIGH);
    digitalWrite(L_CTRL2, HIGH);
    analogWrite(L_PWM, 0);
}
/*******************************************************************************/
void rightMotor(int motorPower)
{
    motorPower = constrain(motorPower, -255, 255);   // constrain motorPower to -255 to +255
    if(motorPower >= 0)
    {
        // spin CW
        digitalWrite(R_CTRL1, HIGH);
        digitalWrite(R_CTRL2, LOW);
        analogWrite(R_PWM, abs(motorPower));
    }
    else
    {
        // spin CCW
        digitalWrite(R_CTRL1, LOW);
        digitalWrite(R_CTRL2, HIGH);
        analogWrite(R_PWM, abs(motorPower));
    }
}

/*******************************************************************************/
void rightBrake()
{
    // setting both controls HIGH, shorts the motor out -- causing it to self brake.
    digitalWrite(L_CTRL1, HIGH);
    digitalWrite(L_CTRL2, HIGH);
    analogWrite(R_PWM, 0);
}

int get_distance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  return distance;
}


void loop() {
  if (Serial.available()>0){
    int val = Serial.read() - '0';
    if (val==0) {
      leftMotor(255);
      rightMotor(-255);
    }
    if (val==1) {
      leftMotor(-255);
      rightMotor(255);
    }
    if (val==2) {
      leftMotor(255);
      rightMotor(255);
    }
    if (val==3) {
      leftMotor(-255);
      rightMotor(-255);
    }
    if (val==4) {
      leftBrake();
      rightBrake();
    }
    if (val == 5) {
      if (inc>30) {
        inc = inc - 30;
        myservo.write(inc);                  // sets the servo position left
        delay(15);
      }
    }
    if (val == 6) {
      if (inc<150) {
        inc = inc + 30;
        myservo.write(inc);                  // sets the servo position left
        delay(15);
      }
    }
    if (val == 7) {
      if (inc2>30) {
        inc2 = inc2 - 30;
        myservo2.write(inc2);                  // sets the servo position left
        delay(15);
      }
    }
    if (val == 8) {
      if (inc2<150) {
        inc2 = inc2 + 30;
        myservo2.write(inc2);                  // sets the servo position left
        delay(15);
      }
    }
  }
}
