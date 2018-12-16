/* reads a distance sensor on pin 2
    if smaller than the threshold
    atrips a relay on pin 13
*/



int sensor = 2; //ultrasonic distance sensor
int trigPin = 4; //TRIG pin, to sens out a pulse to receive back
int threshold =100; // in cms
int output = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(output, OUTPUT);
}

void loop()
{
  
  digitalWrite(trigPin, HIGH); //Trigger ultrasonic detection
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int distance = pulseIn(sensor, HIGH); //Read ultrasonic reflection
  distance = distance / 58; //Calculate distance


if(distance<threshold){
  digitalWrite(output,HIGH);
  delay(100);
  }
else{
 digitalWrite(output,LOW); 
  }
}

