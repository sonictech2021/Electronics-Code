// Electronics Code V2

/* 
Notes: This is the second interation of my code which improves on the previous version by introducing an 
automatic brightness feature where the brightness of the LEDs can change depending on the brightness of the surrounding environment. 
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN    8
#define LED_COUNT  8
#define BUTTON_PIN 7
#define LDR_PIN    A0 /* The pin that the LDR (Light Dependant Resistor) is connected to. Because it provides an 
                         analogue output, it is connected to the analogue pin on the Arduino. */

boolean previousState = HIGH;
int effect = 1;
int LDR_VALUE = 0;
int brightness = 50;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}


void loop() {

  {
  LDR_VALUE = analogRead(LDR_PIN);
  strip.setBrightness( map(LDR_VALUE, 0, 200, 1, 255)); /* Mapping the LDR to fit the range of the 
                                                           brightness levels that the NeoPixel can display.*/
  Serial.println(LDR_VALUE);
  strip.show();
  delay(30);
  } 

  boolean newState = digitalRead(BUTTON_PIN);
  
  if((newState == LOW) && (previousState == HIGH)) {
    delay(20);
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {
      if(++effect > 8) effect = 1;
      switch(effect) { // This is the list of lighting effects and colours, the button will cycle through these effects when pressed.
        case 1: // WHITE
          colorWipe(strip.Color(255, 255, 255), 0);
          break;
        case 2: // RED
          colorWipe(strip.Color(255, 0, 0), 0);
          break;
        case 3: // ORANGE
          colorWipe(strip.Color(255, 70, 0), 0);
          break;
        case 4: // YELLOW
          colorWipe(strip.Color(255, 255, 0), 0);
          break;
        case 5: // GREEN
          colorWipe(strip.Color(0, 255, 0), 0);
          break;
        case 6: // BLUE
          colorWipe(strip.Color(0, 0, 255), 0);
          break;
        case 7: // PURPLE
          colorWipe(strip.Color(255, 0, 255), 0);
          break;
        case 8: // OFF
          colorWipe(strip.Color(0, 0, 0), 0);
          break;
      }
    }
  }
  previousState = newState;
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                   
    delay(wait);                           
  }
}
