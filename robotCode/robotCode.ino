// Wall Doding robot code
// Jaycar Electronics 2020
// 9V battery version - startup delay, less turns (higher voltage = faster turns)

#include <AFMotor.h>

const int ldr_pin = A5;
const int trigger_pin = A2;
const int echo_pin = A3;

const int light_threshold = 700;
const int sonar_threshold = 200;

AF_DCMotor left_motor(4);
AF_DCMotor right_motor(3);

const int motor_speed = 150;

//define the functions so we can use them later.

void setup()
{
  Serial.begin(9600);
  Serial.println("Robot Starting!");
  Serial.println("Delay..");

  for (int i = 5; i > 0; i--)
  {
    Serial.print(i, DEC);
    Serial.println("...");
    delay(1000);
  }

  pinMode(ldr_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.println("Robot OK!");
}

void loop()
{
  delay(100);

  int ldrReading = analogRead(ldr_pin);
  long sonarDistance = sonarPing();

  Serial.print("LDR Reading: ");
  Serial.println(ldrReading, DEC);
  Serial.print("Distance Reading: ");
  Serial.println(sonarDistance, DEC);

  //check if the lights are on
  if (ldrReading < light_threshold)
  {
    stop();
    blinkErrorMessage();
    //return as we don't want to do more in the loop function
    return;
  }

  // check distance of what's in front of us
  // (closer objects are lower values)
  if (sonarDistance < sonar_threshold)
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
  left_motor.setSpeed(motor_speed);
  right_motor.setSpeed(motor_speed);
}
void driveBackward(long time)
{
  left_motor.run(BACKWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(motor_speed);
  right_motor.setSpeed(motor_speed);
  delay(time); //drive backwards for half a second
}
void stop()
{
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(500); //stop for half a second, allow motors to wind down
}
void reverseTurn(long time)
{
  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(0);
  right_motor.setSpeed(motor_speed);
  delay(time);
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
