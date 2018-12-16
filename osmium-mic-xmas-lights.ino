*
 * mic sensor in pin A0
 * xmas light s on a relay on pin 5
 * 
 * when the noise level gets over the threshold value the 
 * relay turns off the xmas lights for 500 milliseconds
 */



const int analogPin = 0;

int threshold = 100; // raise this number if the mic is to sensitive or lower it if not senitive enough

int output = 5;
int outputValue;
 
void setup() {
    Serial.begin(9600);
    pinMode(output,OUTPUT);
}
 
void loop() {
      digitalWrite(output,HIGH);

    int mn = 1024; // mn only decreases
    int mx = 0;    // mx only increases
    int d;
 
    // Perform 10000 reads. Update mn and mx for each one.
    for (int i = 0; i < 2000; ++i) {
        int val = analogRead(analogPin);
        mn = min(mn, val);
        mx = max(mx, val);
        d = mx-mn;
        
    }
outputValue = constrain(d, 0,255);
//analogWrite ( output,outputValue);
 
    // Send min, max and delta over Serial
  //Serial.print("m=");
  //Serial.print(mn);
  //Serial.print(" M=");
  //Serial.print(mx);
  //Serial.print(" D=");
  //Serial.print(d);
  Serial.print("  outputValue = ");
  Serial.println(outputValue);  

    if(d>threshold){
      digitalWrite(output,LOW);
      delay(500);
      Serial.print("triggered");
      digitalWrite(output,HIGH);
      
      }
    Serial.println();
}
