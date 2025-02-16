//The MIT License (MIT)
//
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files (the "Software"), to deal in
//the Software without restriction, including without limitation the rights to
//use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//the Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//Based on FastLED "100-lines-of-code" demo reel
#include <ADCInput.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>


#define DATA_PIN    0
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    19 // one more than in the stip to force a "gap" where the USBC slot is
#define MAX_BRIGHTNESS      200
#define FRAMES_PER_SECOND   120

#define chargingSignalPin A3
CRGB leds[NUM_LEDS];
Adafruit_NeoPixel onboardLED(1, 16, NEO_GRB + NEO_KHZ800);// set neopixle to use the onboard LED

typedef void (*SimplePatternList[])();

void setup() {

  delay(3000); // 3 second delay for recovery
  onboardLED.begin();
  onboardLED.show(); // Initialize onboard LED to 'off'

  Serial.begin(9600);
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(MAX_BRIGHTNESS);
  setRanbow();
}


// List of patterns to cycle through.  Each is defined as a separate function below.

SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gLastLoopPatternNumber = 0;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


bool charging = false;

uint8_t hue_speed = 20;
uint8_t breathe_speed = 20;


unsigned long startMillis; 
unsigned long currentMillis;


void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

  // insert a delay to keep the framerate modest
 // FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( hue_speed ) { gHue++; } // slowly cycle the "base color" through the rainbow

  if (analogRead(chargingSignalPin)<900)
  {
    charging = true;
  }else
  {
    charging = false;
  }

  if(charging)
  {
    onboardLED.setPixelColor(0, 100, 0, 0);
    onboardLED.show();
    EVERY_N_MILLISECONDS (breathe_speed) {addBreathe();}
  }
  else
  {
    onboardLED.clear();
    onboardLED.show();
    EVERY_N_MILLISECONDS (breathe_speed) {fadeIn();}
  }
}

void setRanbow()
{
  gCurrentPatternNumber = 0;
}

uint8_t low_brightness = 10;
uint8_t current_brightness=MAX_BRIGHTNESS;
int8_t brightnesStep = 1;

void addBreathe()
{
  if(current_brightness >= MAX_BRIGHTNESS || current_brightness <= low_brightness)
  {
    brightnesStep *= -1;
  }

  FastLED.setBrightness(current_brightness + brightnesStep);
  current_brightness += brightnesStep;
}

void fadeIn()
{
  brightnesStep=abs(brightnesStep);
  if (current_brightness < MAX_BRIGHTNESS)
  {
    FastLED.setBrightness(current_brightness + brightnesStep);
    current_brightness += brightnesStep;
  }
}


void setRanbowGlitter()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = 1;
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}