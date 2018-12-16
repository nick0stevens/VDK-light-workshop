/* Knock Sensor with UV light via relay

   The circuit:
	* one connection of the piezo attached to analog in A0
	* one connection of the piezo attached to ground
	* 1-megohm resistor attached from analog in 0 to ground

relay with Lamp on pin 13

 */


// these constants won't change:
const int lampPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin

void setup() {
  pinMode(lampPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
    Serial.println(sensorReading);
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {

    digitalWrite(lampPin, HIGH);
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");
    delay(500);
    digitalWrite(lampPin, LOW);

  }
  delay(100);  // delay to avoid overloading the serial port buffer
}
