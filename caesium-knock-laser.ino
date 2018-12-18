/*
thres knock sensor on AO,A1,A2;
activate three lasers on 13,12,11
if knock is sensed above the threshold laser is triggered for 500 milliseconds
*/
int count = 3;           // the number of pins (i.e. the length of the array)

int laser[] = {13, 12, 11};     // an array of pin numbers to which LEDs are attached
int sensor[] = {0, 1, 2};
int sensorReading[3];
int sensorThres[3] = {100, 100, 100};
long startTime[3];

void setup() {
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisLaser = 0; thisLaser < count; thisLaser++) {
    pinMode(laser[thisLaser], OUTPUT);
  }
  Serial.begin(9600);       // use the serial port

}

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisSensor = 0; thisSensor < count; thisSensor++) {
    sensorReading[thisSensor] = analogRead[thisSensor];

    Serial.print(" ");
    Serial.print(thisSensor);
    Serial.print("= ");
    Serial.print(sensorReading[thisSensor]);

    if (sensorReading[thisSensor] > sensorThres[thisSensor]) {
      digitalWrite(laser[thisSensor], HIGH);
      startTime[thisSensor] = millis();
      Serial.print(" ");
      Serial.print(thisSensor);
      Serial.print(" Hit!");

    }

    if (millis() > startTime[thisSensor] + 500) {
      digitalWrite(laser[thisSensor], LOW);
    }
  }

}
