/*
  reads 10 light sensors into an array
  if any sensor reads low the a color sequence it run.

  calibration happens over the first 10 sec when the led on pin 13 is on.

  show the highest and lowest values to the sensors during this time.

*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 5
#define numPix 150
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPix, PIN, NEO_GRB + NEO_KHZ800);


int sensors[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // an array of pin numbers to which LEDs are attached
int sensorCount = 10;           // the number of pins (i.e. the length of the array)
int sensorMin[] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
int sensorReading[10];
int sensorThres[10];

int cup;
boolean scored = false;

void setup() {
  //set each pin as inout
  for (int thisSensor = 0; thisSensor < sensorCount; thisSensor++) {
    pinMode(sensors[thisSensor], INPUT);
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // calibrate min values during the first 10 seconds
  while (millis() < 10000) {
    for (int thisSensor = 0; thisSensor < sensorCount; thisSensor++) {
      sensorReading[thisSensor] = analogRead(thisSensor);
      if (sensorReading[thisSensor] < sensorMin[thisSensor]) {
        sensorMin[thisSensor] = sensorReading[thisSensor];
      }
    }

    // se the threshold for each sensor ( 15 off the min value)
    for (int thisSensor = 0; thisSensor < sensorCount; thisSensor++) {
      sensorThres[thisSensor] = sensorMin[thisSensor] + 15;
    }

    // signal the end of the calibration period
    digitalWrite(13, LOW);
  }
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


}

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisSensor = 0; thisSensor < sensorCount; thisSensor++) {
    sensorReading[thisSensor] = analogRead(thisSensor);
    Serial.print(" ");
    Serial.print(thisSensor);
    Serial.print("= ");
    Serial.print(sensorReading[thisSensor]);

    if (sensorReading[thisSensor] < sensorThres[thisSensor]) {
      scored = true;
      cup = thisSensor;
      Serial.print("Scored! cup = ");
      Serial.println(thisSensor);
    }
  }
  Serial.println();

  if (scored) {
    switch (cup) {
      case (0):

        scored = false;
        break;
      case (8):
        rainbowCycle(10);

        scored = false;
        break;

      default:
        colorWipe(strip.Color(255, 0, 0), 10); // Red
        colorWipe(strip.Color(0, 255, 0), 10); // Green
        scored = false;
        break;
    }
  }



}




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
