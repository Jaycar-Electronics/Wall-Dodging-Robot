// Wall Doding robot code
// Jaycar Electronics 2020

#include <AFMotor.h>

const int ldr_pin = A5;
const int trigger_pin = A4;
const int echo_pin = A3;

const int light_threshold = 600;
const int sonar_threshold = 200;

AF_DCMotor left_motor(4);
AF_DCMotor right_motor(3);

void setup()
{
  Serial.begin(9600);
  Serial.println("Robot Starting!");

  pinMode(ldr_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT); 

  Serial.println("Robot OK!");

}

void loop()
{
  delay(100);

  //check if the lights are on
  if (analogRead(ldr_pin) < light_threshold)
  {
    stop();
    blinkErrorMessage();
    //return as we don't want to do more in the loop function
    return;
  }

  // check distance of what's in front of us
  // (closer objects are lower values)
  if (sonarPing() < sonar_threshold)
  {
    //turn around;
    stop();
    driveBackward(800);
    reverseTurn(400);
    stop();
  }

  //drive forward
  driveForward();
}
// ===============================================================

// ----------------------------------------------------
// blinkErrorMessage function
//   This is to just blink the onboard LED when needed.

void blinkErrorMessage()
{

  pinMode(13, OUTPUT);

  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);

  delay(100);

  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);

  delay(1000);
  pinMode(13, INPUT);
}

// --------------------------------------------------------
// motion functions
//   These just set the correct motor values to drive the bot
void driveForward()
{
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
}
void driveBackward(long time)
{
  left_motor.run(BACKWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
  delay(time); //drive backwards for half a second
}
void stop(){
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(500); //stop for half a second, allow motors to wind down
}
void reverseTurn(long time)
{
  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(0);
  right_motor.setSpeed(255);
  delay(time); //turn for 1 second, overshoots a bit but that's ok
}

// -------------------------------------------------------------
// sonarPing function
//    This measures the distance (in milimeters) to the object infront of it
unsigned long sonarPing()
{
  //send a pulse and time how long it takes to come back.
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  unsigned long duration = pulseIn(echo_pin, HIGH);
  return duration * 0.17; //convert microseconds to millimeters; (speed of sound);
}
