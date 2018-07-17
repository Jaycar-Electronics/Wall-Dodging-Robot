//Ultrasonic sensor pins
#define TRIG 9
#define ECHO 10

//motor module pins
const int channel_a_enable  = 6;
const int channel_a_input_1 = 4;
const int channel_a_input_2 = 7;
const int channel_b_enable  = 5;
const int channel_b_input_3 = 3;
const int channel_b_input_4 = 2;

int a=0;    //motor a speed and direction
int b=0;    //motor b speed and direction
int phase=0;    //what stage are we up to
long timeout=0;    //how long have we been doing it for

#define PROX 30
#define FORWARDSPEED 150
#define REVERSESPEED 150
//set TURNSPEED negative to turn the other way
#define TURNSPEED 150
#define REVERSETIME 1000
#define TURNTIME 1000

void setup()
{
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);    //GND for ultrasonic
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);    //5V for ultrasonic
  
  usonicsetup();
  
  pinMode( channel_a_enable, OUTPUT );  // Channel A enable
  pinMode( channel_a_input_1, OUTPUT ); // Channel A input 1
  pinMode( channel_a_input_2, OUTPUT ); // Channel A input 2
  
  pinMode( channel_b_enable, OUTPUT );  // Channel B enable
  pinMode( channel_b_input_3, OUTPUT ); // Channel B input 3
  pinMode( channel_b_input_4, OUTPUT ); // Channel B input 4
//everything off
  digitalWrite( channel_a_input_1, LOW);
  digitalWrite( channel_a_input_2, LOW);
  digitalWrite( channel_a_enable, LOW);

  digitalWrite( channel_b_input_3, LOW);
  digitalWrite( channel_b_input_4, LOW);
  digitalWrite( channel_b_enable, LOW);
  
  delay(1000);  //wait a bit
  
  Serial.begin( 9600 );    //serial debug
  Serial.println("Starting up");
}

void loop()
{
  //read ultrasonic sensor
  int d;
  d=usonic(11600)/58;  // distance in cm
  if(d==0){d=200;}
  Serial.println(d);    //print d on serial monitor

  //react based on d
  switch(phase){
    case 0:
      if(d<PROX){phase=1;timeout=millis();}    //if too close, reverse
      break;
    case 1:
      if(millis()>timeout+REVERSETIME){phase=2;timeout=millis();}    //reversed for REVERSETIME, now turn
      break;
    case 2:
      if(millis()>timeout+TURNTIME){phase=0;}    //turned for TURNTIME, now back to forward
      break;
  }
  
  //print phase for debugging
  Serial.print("PHASE:");
  Serial.println(phase);

  //set motors based on stage
  switch(phase){
    case 0:    //normal going forward
      a=FORWARDSPEED;
      b=FORWARDSPEED;
      break;
    case 1:    //backing up
      a=-(REVERSESPEED);
      b=-(REVERSESPEED);
      break;
    case 2:    //turn a little
      a=TURNSPEED;
      b=-(TURNSPEED);
      break;
    default:      //something wrong happened
      a=0;
      b=0;
      break;
  }
  setmotor();    
  delay(200);    //wait a bit
}

void setmotor(){
  int s;
  
  if(a>0){
      digitalWrite( channel_a_input_1, HIGH);
      digitalWrite( channel_a_input_2, LOW);
  }
  if(a<0){
      digitalWrite( channel_a_input_1, LOW);
      digitalWrite( channel_a_input_2, HIGH);
  }
  if(b>0){
      digitalWrite( channel_b_input_3, HIGH);
      digitalWrite( channel_b_input_4, LOW);
  }
  if(b<0){
      digitalWrite( channel_b_input_3, LOW);
      digitalWrite( channel_b_input_4, HIGH);
  }

  s=abs(a);
  if(s>255){s=255;}
  if(s<0){s=0;}
  analogWrite( channel_a_enable, s);
  
  s=abs(b);
  if(s>255){s=255;}
  if(s<0){s=0;}
  analogWrite( channel_b_enable, s);
  
}  


void allInputsOff()
{
  digitalWrite( channel_a_input_1, LOW);
  digitalWrite( channel_a_input_2, LOW);
  digitalWrite( channel_a_enable, LOW);

  digitalWrite( channel_b_input_3, LOW);
  digitalWrite( channel_b_input_4, LOW);
  digitalWrite( channel_b_enable, LOW);
}

void usonicsetup(void){
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
}

long usonic(long utimeout){    //utimeout is maximum time to wait for return in us
  long b;
  if(digitalRead(ECHO)==HIGH){return 0;}    //if echo line is still low from last result, return 0;
  digitalWrite(TRIG, HIGH);  //send trigger pulse
  delay(1);
  digitalWrite(TRIG, LOW);
  long utimer=micros();
  while((digitalRead(ECHO)==LOW)&&((micros()-utimer)<1000)){}  //wait for pin state to change- return starts after 460us typically
  utimer=micros();
  while((digitalRead(ECHO)==HIGH)&&((micros()-utimer)<utimeout)){}  //wait for pin state to change
  b=micros()-utimer;
  return b;
}
 

