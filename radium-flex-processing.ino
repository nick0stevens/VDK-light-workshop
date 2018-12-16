/* this sketch reads a sensor on A0
    maps the values 
    and write value to serial port for processing
*/



int sensor= A0;
int sensorValue;
int sensorMin = 320;
int sensorMax = 650;


int outputValue;


void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop()
{

  sensorValue = analogRead(sensor);

  //Serial.print("sensorValue = ");
  //Serial.println(sensorValue);

  outputValue = map(sensorValue, sensorMin, sensorMax, 400, 0);
  outputValue = constrain(outputValue, 0, 400);

  //Serial.print("  outputValue = ");
  //Serial.println(outputValue);

Serial.print(outputValue);
Serial.print(',');
Serial.print(outputValue);
Serial.print(',');
Serial.println(outputValue);
delay(10);




}



/*
 * processing code

This processing code reads and parses serial input
// you will need to confirm that port number of your 
arduino is correct;


import processing.serial.*;

Serial myPort; // The serial port wont be able to connect if the seril monitor in arduino is open so make sure to close it
String inBuffer = null; // stores one line of data from serial port

float x, y, z;
int lf = 10; // Linefeed in ASCII


void setup() {
size(640, 360);
noStroke();
// the for loop below prints all serial ports available on your computer, listed from 0 onwards
// ie. the first one on the list is actually port zero and the sixth is port 5


for(int i = 0; i<Serial.list().length; i++){
println(i+"-"+Serial.list()[i]);
}

// find the one that is used by the ardunio and enter the number into the [] brackets below, and ensure that the baud rate on your ardunio is 9600
myPort = new Serial(this, Serial.list()[3], 9600);

}


void draw() {
background(150);
ellipseMode(CENTER);

fill(255,0,0);
ellipse(width/4*1,height/2,x+20,x+20);
fill(0,255,0);
ellipse(width/4*2,height/2,y+20,y+20);
fill(0,0,255);
ellipse(width/4*3,height/2,z+20,z+20);


}

// this code is called automatically when there is data available in the serial port


void serialEvent(Serial myPort) {
inBuffer = myPort.readStringUntil(lf); // store serial port buffer in global var inBuffer (read string until linefeed (int lf = 10; // Linefeed in ASCII) etc
if (inBuffer != null) {
println("SERIAL:" + inBuffer); // print the line from then serial input
try {
float[] dat = float(split(inBuffer, ',')); // parse comma-separated number string into numbers array
x= dat[0];
y= dat[1];
z= dat[2];

}
catch (Exception e) { // if there is a non parsible string its declared null
inBuffer=null;
}

}
}
*/
 
