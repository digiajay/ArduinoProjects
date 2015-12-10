/*
  Serial WS2812 RGB controller

*/
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define LED_COUNT 1

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

String inString;    // string to hold input
int currentColor = 0;
int red, green, blue = 0;

void setup() {
  // Open serial communications and wait for port to open:
  leds.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  int inChar;
  
  // Read serial input:
  if (Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (isDigit(inChar)) {
    // convert the incoming byte to a char
    // and add it to the string:
    inString += (char)inChar;
  }

    if (inChar == ',') {
    switch (currentColor) {
      case 0:    // 0 = red
        red = inString.toInt();
        // clear the string for new input:
        inString = "";
        Serial.println(String(red,BIN));
        break;
      case 1:    // 1 = green:
        green = inString.toInt();
        // clear the string for new input:
        inString = "";
        Serial.println(String(green,BIN));
        break;
    }
    currentColor++;
    
  }
  // if you get a newline, you know you've got
  // the last color, i.e. blue:
  if (inChar == '\n') {
    blue = inString.toInt();
    Serial.println(currentColor);
 
    leds.setPixelColor(0, red, green, blue);
    leds.show();

    // clear the string for new input:
    inString = "";
    // reset the color counter:
    currentColor = 0;
  }

}
