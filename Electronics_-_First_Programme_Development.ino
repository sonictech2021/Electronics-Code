// Electronics Code V1

/* Notes: This is the initial code development which uses the Adafruit NeoPixel library. There are a few lighting effects that can be controlled by a button. */

#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library in this program.
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN    8 // The pin that the NeoPixel RGB LEDs are connected to.
#define LED_COUNT  12 // The number of NeoPixel RGB LEDs daisychained together.
#define BUTTON_PIN 7 // The pin that the tactile push button is connected to.

boolean previousState = HIGH;
int effect = 1; // Initial lighting effect upon startup.
int brightness = 80; // Initial brightness of the LEDs.


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Sets the pinmode as an input, by enabling the internal pullup resistor for the input, there is no need to add a pull up resistor.

}


void loop() {

  boolean newState = digitalRead(BUTTON_PIN);
  
  if((newState == LOW) && (previousState == HIGH)) {
    delay(20);
    newState = digitalRead(BUTTON_PIN); // Sets the newState value as the input value from the button through a debounce program to ensure each press only registers as one press.
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
