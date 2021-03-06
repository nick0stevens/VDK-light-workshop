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
 Processing code

reads serial port for sensor data from arduino
 use web cam to obtain black and white image, if sensor data is above threhold
 a full colour image is saved and shown for a few moments
 
 




import processing.video.*;
import processing.serial.*;

Serial myPort; // The serial port wont be able to connect if the seril monitor in arduino is open so make sure to close it
String inBuffer = null; // stores one line of data from serial port

float x, y, z;
int lf = 10; // Linefeed in ASCII

color black = color(0);
color white = color(255);
int numPixels;
boolean snapped = false;
boolean pushed = false;
long snapTime;


int[] previousFrame;

int threhold = 20;
int counter = 0;
Capture video;

void setup() {
  
  //fullScreen();
  size(1920, 1080); // Change size to 320 x 240 if too slow at 640 x 480
  strokeWeight(5);
  
  String[] cameras = Capture.list();

  if (cameras == null) {
    println("Failed to retrieve the list of available cameras, will try the default...");
    video = new Capture(this, 640, 480);
  } if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    printArray(cameras);

    // The camera can be initialized directly using an element
    // from the array returned by list():
    video = new Capture(this, cameras[0]);
    // Or, the settings can be defined based on the text in the list
    //cam = new Capture(this, 640, 480, "Built-in iSight", 30);
    
    // Start capturing the images from the camera
    video.start();
  }
   numPixels = width* height;
   
     previousFrame = new int[numPixels];
  loadPixels();
  noCursor();
  smooth();
  
  for(int i = 0; i<Serial.list().length; i++){
println(i+"-"+Serial.list()[i]);
}

// find the one that is used by the ardunio and enter the number into the [] brackets below, and ensure that the baud rate on your ardunio is 9600
myPort = new Serial(this, Serial.list()[3], 9600);

  
}

void draw() {
 

  if (video.available()) {
    video.read();
    
 if(pushed){
if(!snapped){
  image(video, 0, 0);
  
  counter ++;
  String fileName = "flexCam" + counter;
  save(fileName);
  snapped = true;
  snapTime = millis();
  println("snapped");
}
  }
    
    
  else{  
video.loadPixels(); // Make its pixels[] array available
    
    int movementSum = 0; // Amount of movement in the frame
    for (int i = 0; i < numPixels; i++) { // For each pixel in the video frame...
      color currColor = video.pixels[i];
      color prevColor = previousFrame[i];
      // Extract the red, green, and blue components from current pixel
      int currR = (currColor >> 16) & 0xFF; // Like red(), but faster
      int currG = (currColor >> 8) & 0xFF;
      int currB = currColor & 0xFF;
      // Extract red, green, and blue components from previous pixel
      int prevR = (prevColor >> 16) & 0xFF;
      int prevG = (prevColor >> 8) & 0xFF;
      int prevB = prevColor & 0xFF;
      // Compute the difference of the red, green, and blue values
      int diffR = abs(currR - prevR);
      int diffG = abs(currG - prevG);
      int diffB = abs(currB - prevB);
      // Add these differences to the running tally
      movementSum += diffR + diffG + diffB;
      // Render the difference image to the screen
      pixels[i] = color(diffR, diffG, diffB);
      // The following line is much faster, but more confusing to read
      //pixels[i] = 0xff000000 | (diffR << 16) | (diffG << 8) | diffB;
      // Save the current color into the 'previous' buffer
      previousFrame[i] = currColor;
    }
    // To prevent flicker from frames that are all black (no movement),
    // only update the screen if the image has changed.
    if (movementSum > 0) {
      updatePixels();
      println(movementSum); // Print the total amount of movement to the console
    }
  }
  
  }
 if(millis()>snapTime+2000){
   if(snapped){
  snapped= false;
  pushed = false;
  //println("finnished");
  }
 }
 
 if(x>threhold){
 pushed = true;
 println("flexed");
 }
 
}

void keyPressed() {
  switch (key) {
    case ' ':   {pushed = true;
  println("pushed");} break;
  }
}



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
