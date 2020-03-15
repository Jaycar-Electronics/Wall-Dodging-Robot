int ledPin = 13;                // choose the pin for the LED
int inputPin = D2;               // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status
 
void setup()
{
  delay(1000);
  Serial.println();  
  Serial.println("Initiated...");  
 
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop()
{
  Serial.println("in the loop");      
 
  val = digitalRead(inputPin);  // read input value
 
  if (val == HIGH)
  {            
    // we have just turned on
    Serial.println("Motion detected!");

    delay(1000);
  }
  else
  {
    // we have just turned on
    Serial.println("No motion detected!");

    delay(1000);
  }
}
