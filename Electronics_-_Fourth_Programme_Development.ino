// Electronics Code V4

/* Notes: This is the fourth and final interation of my code which improves on the previous version by implementing Bluetooth connectivity which allows users to control the light with their smartphone. */

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
int autobrightness = 100;
int set = 80;
byte receivedNumber = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <SoftwareSerial.h> 
SoftwareSerial control(0, 1); // RX | TX

void setup() {

  Serial.begin(9600);
  control.begin(9600);
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT_PULLUP);

}


void loop() {
  
  onoff();
  
//---------------------------------------------------------------------------------------

  if (control.available()) 
  effect = control.read();
  Serial.write(control);
       //------------------------------------------
       if (effect == 'a') // OFF
       {
        colorWipe(strip.Color(0, 0, 0), 0);    
       }
       //------------------------------------------
       if (effect == 'r') // RED
       {
        colorWipe(strip.Color(255, 0, 0), 0);    
       }
       //------------------------------------------
       if (effect == 'o') // ORANGE
       {
        colorWipe(strip.Color(255, 165, 0), 0);    
       }
       //------------------------------------------
       if (effect == 'y') // YELLOW
       {
        colorWipe(strip.Color(255, 255, 0), 0); 
       }
       //------------------------------------------
       if (effect == 'g') // GREEN
       {
        colorWipe(strip.Color(0, 255, 0), 0); 
       }
       //------------------------------------------
       if (effect == 'b') // BLUE
       {
        colorWipe(strip.Color(0, 0, 255), 0); 
       }
       //------------------------------------------
       if (effect == 'l') // LIGHTBLUE
       {
        colorWipe(strip.Color(0, 185, 255), 0); 
       }
       //------------------------------------------
       if (effect == 'p') // PURPLE
       {
        colorWipe(strip.Color(255, 0, 255), 0); 
       }
       //------------------------------------------
       if (effect == 'w') // WHITE
       {
        colorWipe(strip.Color(255, 255, 255), 0); 
       }
       //------------------------------------------
       if (effect == 'z')
       {
        LDR_VALUE = analogRead(LDR_PIN);
        strip.setBrightness( map(LDR_VALUE, 0, 300, 1, 255));
        Serial.println(LDR_VALUE);
        strip.show();
        delay(30);
       }
       //------------------------------------------
       if (effect == 'u')
       {
        strip.setBrightness(autobrightness + set);
        strip.show();
       }
       //------------------------------------------
       if (effect == 'd')
       {
        strip.setBrightness(autobrightness - set);
        strip.show();
       }

//---------------------------------------------------------------------------------------


  boolean touchnewState = digitalRead(TOUCH_PIN);
    if((touchnewState == LOW) && (previousState == HIGH)) {
      delay(20);
      touchnewState = digitalRead(TOUCH_PIN);
      if(touchnewState == LOW) {
        if(++effect > 8) effect = 1;
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
          case 7: // LIGHTBLUE
            colorWipe(strip.Color(0, 185, 255), 0);
            onoff();
            break;
          case 8: // PURPLE
            colorWipe(strip.Color(255, 0, 255), 0);
            onoff();
            break;
        }
      }
    }
    previousState = touchnewState;
}

//---------------------------------------------------------------------------------------


void onoff() {
  power = digitalRead(BUTTON_PIN);
  Serial.print(power);
  if(power == LOW) {
    colorWipe(strip.Color(0, 0, 0), 0);
    delay(50);
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
