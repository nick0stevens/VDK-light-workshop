/* this sketch reads a distance sensor with 
 *  echo pin on pin 2
 *  trigger pin on pin 4
    maps the values and then outputs to halogen on  pin 5
   
*/



int sensor = 2; //ultrasonic distance sensor
int trigPin = 4; //TRIG pin, to sens out a pulse to receive back
int sensorValue;
int sensorMin = 40;
int sensorMax = 200;

int output = 5;
int outputValue;


void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(output, OUTPUT);
}

void loop()
{
  delay(100);
  digitalWrite(trigPin, HIGH); //Trigger ultrasonic detection
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int distance = pulseIn(sensor, HIGH); //Read ultrasonic reflection
  distance = distance / 58; //Calculate distance
  sensorValue = distance;

  Serial.print("sensorValue = ");
  Serial.print(sensorValue);

  outputValue = map(sensorValue, sensorMin, sensorMax, 255, 50);
  if(outputValue<50){outputValue = 0;}
  outputValue = constrain(outputValue, 0, 255);

  Serial.print("  outputValue = ");
  Serial.println(outputValue);

  analogWrite(output, outputValue);


}
