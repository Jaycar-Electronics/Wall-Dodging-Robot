
// Wall Doding robot code
// Written by D.West
// Jaycar Electronics 2019

const int aChannelEnable = 3; //PWM pin
const int bChannelEnable = 9; //PWM pin

const int inA1 = 7;
const int inA2 = 6;

const int inB1 = 5;
const int inB2 = 4;

#define ULTRASONIC_VCC 11

//ultrasonic trigger and echo
const int usTrigger = 12;   //output
const int usEcho = 13;      //input
const int lightSensor = A0; //analog input

const int motorSpeed = 125;

const int lightShutoffLevel = 600;
const int sonarThreshhold = 200;

// ----------------------------------------------------

void setup()
{

  Serial.begin(115200);
  Serial.println("OK");

  //motor controller pins
  pinMode(aChannelEnable, OUTPUT); //output from the arduino -> motor controller
  pinMode(bChannelEnable, OUTPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

  // ------------ drive the VCC high, kinda hacky.
  pinMode(ULTRASONIC_VCC, OUTPUT);
  digitalWrite(ULTRASONIC_VCC, HIGH);
  // ---------------------------------

  //sensors and inputs
  pinMode(usTrigger, OUTPUT);
  pinMode(usEcho, INPUT);
  pinMode(lightSensor, INPUT);

  Serial.println("Robot ready to go!");
}

void loop()
{
  delay(100);

  //check if the lights are on
  if (analogRead(lightSensor) < lightShutoffLevel)
  {

    setMotorSpeed('A', 0);
    setMotorSpeed('B', 0);
    blinkErrorMessage();
    //return as we don't want to do more in the loop function
    return;
  }

  // check distance of what's in front of us
  // (closer objects are lower values)
  if (sonarPing() < sonarThreshhold)
  {
    //turn around;
    driveBackward();
    reverseTurn();
  }

  //drive forward
  driveForward();
}

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

  setMotorSpeed('A', motorSpeed);
  setMotorSpeed('B', motorSpeed);
}
void driveBackward()
{
  setMotorSpeed('A', -motorSpeed);
  setMotorSpeed('B', -motorSpeed);
  delay(500); //drive for half a second
}

void reverseTurn()
{

  setMotorSpeed('A', 0);
  setMotorSpeed('B', -motorSpeed);
  delay(1000); //turn for 1 second, overshoots a bit but that's ok
}

// -------------------------------------------------------------
// sonarPing function
//    This measures the distance (in milimeters) to the object infront of it

unsigned long sonarPing()
{

  //send a pulse and time how long it takes to come back.

  digitalWrite(usTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(usTrigger, LOW);

  unsigned long duration = pulseIn(usEcho, HIGH);

  return duration * 0.17; //convert microseconds to milimeters; (speed of sound);
}

// ----------------------------------------------------------------
// setMotorSpeed function
//   This writes PWM values to the motor controller for the correct motor

void setMotorSpeed(char motor, int speed)
{

  bool reverse = false;

  if (speed < 1)
  {
    reverse = true;
  }

  if (motor == 'a' || motor == 'A')
  {
    digitalWrite(inA1, reverse ? HIGH : LOW);
    digitalWrite(inA2, reverse ? LOW : HIGH);

    //we only send positive values to analogWrite function
    analogWrite(aChannelEnable, abs(speed));
  }
  else if (motor == 'b' || motor == 'B')
  {
    digitalWrite(inB1, reverse ? HIGH : LOW);
    digitalWrite(inB2, reverse ? LOW : HIGH);

    //we only send positive values to analogWrite function
    analogWrite(bChannelEnable, abs(speed));
  }
  else
  {
    Serial.print("Wrong motor char, not sure what '");
    Serial.print(motor);
    Serial.println("' is");
  }
}