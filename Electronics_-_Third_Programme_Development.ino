// Electronics Code V3

/* Notes: This is the third interation of my code which improves on the previous version by implementing a multifunctional button with a tactile button and a touch sensor. */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN    8
#define LED_COUNT  8
#define BUTTON_PIN 6
#define TOUCH_PIN  7
#define LDR_PIN    A0

boolean previousState = HIGH;
int effect = 1;
int power = 1;
int LDR_VALUE = 0;
int brightness = 50;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT_PULLUP);

}


void loop() {
  
  onoff();
  {
  LDR_VALUE = analogRead(LDR_PIN);
  strip.setBrightness( map(LDR_VALUE, 0, 200, 1, 255));
  //Serial.println(LDR_VALUE);
  strip.show();
  delay(30);
  } 

  boolean touchnewState = digitalRead(TOUCH_PIN);
    if((touchnewState == LOW) && (previousState == HIGH)) {
      delay(20);
      touchnewState = digitalRead(TOUCH_PIN);
      if(touchnewState == LOW) {
        if(++effect > 7) effect = 1;
        switch(effect) {
          case 1: // WHITE
            colorWipe(strip.Color(255, 255, 255), 0);
            onoff();
            break;
          case 2: // RED
            colorWipe(strip.Color(255, 0, 0), 0);
            onoff();
            break;
          case 3: // ORANGE
            colorWipe(strip.Color(255, 70, 0), 0);
            onoff();
            break;
          case 4: // YELLOW
            colorWipe(strip.Color(255, 255, 0), 0);
            onoff();
            break;
          case 5: // GREEN
            colorWipe(strip.Color(0, 255, 0), 0);
            onoff();
            break;
          case 6: // BLUE
            colorWipe(strip.Color(0, 0, 255), 0);
            onoff();
            break;
          case 7: // PURPLE
            colorWipe(strip.Color(255, 0, 255), 0);
            onoff();
            break;
        }
      }
    }
    previousState = touchnewState;
}


void onoff() {
  power = digitalRead(BUTTON_PIN);
  Serial.print(power);
  if(power == LOW) {
    colorWipe(strip.Color(0, 0, 0), 0);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                   
    delay(wait);                           
  }
}
