/* tilt switch with disco lamp via relay
 * 
 * tilt swithc with pullup resistor on pin 2
 * 
 * lamp on pin 13
 * 
 * 
 */
 
int sensor = 2;
bool sensorState;
bool triggered = false;
bool started = false;

int output = 13;


long triggerTime, stateStart;

void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(output,OUTPUT);
  Serial.begin(9600);

}


void loop() {

  if (digitalRead(sensor) == HIGH) {

    if(!triggered){  
    triggered =true;
    triggerTime = millis();   
    }
    if(millis()>triggerTime + 100){
      if(!started){
      sensorState = HIGH;
      stateStart = millis();
      started = true;
      startingOutput();
      }
    }
  }
  else {
    sensorState = LOW ;
    triggered =false;
    started = false;
  }

}

void startingOutput(){
  // put the output code here
  Serial.println("output running");
  digitalWrite(output,HIGH);
  delay(2000);
  digitalWrite(output,LOW);

  }
