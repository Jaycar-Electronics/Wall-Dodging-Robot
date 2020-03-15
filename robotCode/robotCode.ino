// Wall Dodging robot code
// Jaycar Electronics 2020

// Libraries

#include <AFMotor.h>

// Constants

// LDR Sensor Pins
const int LIGHT_LEVEL_SENSOR_PIN = A5;

// Sonar Sensor Pins
const int SONAR_SENSOR_TRIGGER_PIN = A2;
const int SONAR_SENSOR_ECHO_PIN = A3;

const int MINIMUM_LIGHT_LEVEL = 700;

const unsigned long SAFE_DISTANCE_TO_OBJECT = 200; // in mm

const bool TEST_MODE_ON = false;

// Global variables

bool motors_stopped = true;

// Objects

AF_DCMotor left_motor(4);

AF_DCMotor right_motor(3);

void setup()
{

  Serial.begin(9600);

  Serial.println("Robot Starting!");

  // set Digital Pin 13 (Onboard LED) to Output
  pinMode(13, OUTPUT);

  // set LDR Sensor Pin to Input
  pinMode(LIGHT_LEVEL_SENSOR_PIN, INPUT);

  // set Sonar Sensor Pin to Input
  pinMode(SONAR_SENSOR_TRIGGER_PIN, OUTPUT);

  pinMode(SONAR_SENSOR_ECHO_PIN, INPUT);

  Serial.println("Robot Started!");
}

void loop()
{

  delay(100);

  int current_light_level = analogRead(LIGHT_LEVEL_SENSOR_PIN);

  if (TEST_MODE_ON)
  {
    Serial.print("Light Level Reading: ");
    Serial.println(current_light_level, DEC);
  }

  // check whether there is enough light to operate the Robot
  if (current_light_level < MINIMUM_LIGHT_LEVEL)
  {

    // not enough light, so stop the robot and flash the onboard LED
    // until we have enough light again

    if (motors_stopped == false)
      stopMotors();

    flashOnBoardLED();
  }

  else
  {

    // check whether the Robot is too close to an object in front

    unsigned long distance_to_object = getObjectDistance();

    if (TEST_MODE_ON)
    {
      Serial.print("Distance Reading: ");
      Serial.println(distance_to_object, DEC);
    }

    if (distance_to_object < SAFE_DISTANCE_TO_OBJECT)
    {

      // Robot is too close,
      // so stop, reverse for a certain distance and
      // then reverse turn to the right for a certain distance

      stopMotors();

      driveBackward(800);

      reverseTurnRight(800);

      stopMotors();
    }

    // drive the robot forward

    driveForward();

    motors_stopped = false;
  }
}

// ===============================================================

// ----------------------------------------------------

// flash onboard LED function

// flashes the onboard LED twice
// NOTE: the onboard LED on an UNO is on Digital Pin 13

void flashOnBoardLED()
{

  // turn LED on for 200ms, then off
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);

  // wait for 100ms
  delay(100);

  // turn LED on for 200ms, then off
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);

  // wait for 1 second
  delay(1000);
}

// --------------------------------------------------------
// motor shield functions

// calls the motor shield library functions
// that control the speed and direction of the motors

void driveForward()
{

  left_motor.run(FORWARD);
  right_motor.run(FORWARD);

  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
}

void driveBackward(long drive_time)
{

  left_motor.run(BACKWARD);
  right_motor.run(BACKWARD);

  left_motor.setSpeed(255);
  right_motor.setSpeed(255);

  // keep driving backwards
  // for the drive_time period
  delay(drive_time);
}

void reverseTurnRight(long drive_time)
{

  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);

  left_motor.setSpeed(0);
  right_motor.setSpeed(255);

  // keep reverse turning
  // for the drive_time period
  delay(drive_time);
}

void stopMotors()
{

  left_motor.setSpeed(0);
  right_motor.setSpeed(0);

  // half second delay for motors to wind down
  delay(500);

  motors_stopped = true;
}

// -------------------------------------------------------------
// Sonar sensor functions

// returns the distance (in millimeters)
// to any object in front of robot

unsigned long getObjectDistance()
{

  // make the sensor send a sound wave
  digitalWrite(SONAR_SENSOR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_SENSOR_TRIGGER_PIN, LOW);

  // measure how long it takes for the wave to come back (in microseconds)
  unsigned long wave_trip_time = pulseIn(SONAR_SENSOR_ECHO_PIN, HIGH);

  // return the distance to the object (in millimetres)
  // by converting the trip time (in microseconds) to a distance value

  // NOTE

  // We use 0.17 below because the formula for calculating the distance
  // can be expressed as: trip time multipled by half of the speed of sound

  // As the speed of sound through air is 0.343mm per microsecond,
  // we multiply the trip time by 0.17 (because half of 0.343 is 0.17)

  return (wave_trip_time * 0.17);
}
