
/* 
 * Example of using the ChainableRGB library for controlling a Grove RGB.
 * This code puts a red dot (led) moving along a strip of blue dots.
 */

#include <ChainableLED.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

//ws2802
#define PIN             6
#define PIN1            5

#define NUMPIXELS      39

//RGB chainable
#define NUM_LEDS        1

int delayval = 500; // delay for half a second
float hue = 0.0;
boolean up = true;
long start_strip = 0;
long start_strip1 = 0;
long start_RGB = 0;
long start_scroll = 0;
byte power = 0;

ChainableLED leds(7, 8, NUM_LEDS);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);


void setup()
{
  strip.begin(); // This initializes the NeoPixel library.
  strip1.begin();
  //strip.setBrightness(30);
  //strip1.setBrightness(30);
  start_strip = millis();
  delay(500);
  start_strip1 = millis();
  start_scroll = millis();
}

void loop()
{    
  static int rgbCnt = 0; 
  static int clear_flag = true;
     
    if(rgbCnt >= 7)
    {
      static int i = 0;
      static int color = 0;      

      if(clear_flag)
      {
        clear_flag = false;
        
        strip1.clear();
        strip.clear();
        strip.show();  
        strip1.show();  
      }
      
      if(millis() - start_scroll > 60)
      {
        start_scroll = millis();
        if(i++ >= NUMPIXELS)
        {
          i = 0;
          rgbCnt = 0;
          color ++;
          if(color >= 3){
            color = 0;  
          }      
        }
        switch(color)
        {
          case 0:
            strip.setPixelColor(i, strip.Color(0,255,255)); // Moderately bright green color. 
            strip1.setPixelColor(i, strip1.Color(255,0,255)); // Moderately bright green color.            
            break;
          case 1:
            strip.setPixelColor(i, strip.Color(255,0,255)); // Moderately bright red color.  
            strip1.setPixelColor(i, strip1.Color(0,255,255)); // Moderately bright red color.            
            break;        
          case 2:
            strip.setPixelColor(i, strip.Color(255,255,0)); // Moderately bright blue color.  
            strip1.setPixelColor(i, strip1.Color(255,255,255)); // Moderately bright blue color.            
            break;
          default:
            break;        
        }   
        strip.show(); // This sends the updated pixel color to the hardware.      
        strip1.show(); // This sends the updated pixel color to the hardware.      
      }
    }  
    else{
      clear_flag = true;
      if(millis() - start_strip >= 2000) { 
        rgbCnt++;
        start_strip = millis();    
        strip1.clear();
        strip1.show();    
        colorWheel();
        delay(200);    
      }
      if(millis() - start_strip1 >= 2000) { 
        start_strip1 = millis();
        strip.clear();
        strip.show();    
        colorWheel1();   
        delay(200); 
      }
    }  
  if(millis() - start_RGB >= 5)
  {   
    static bool flip = true;
    static int off_time = 0;
    static int color = 0;
    
    start_RGB = millis();        
    
    if(flip)
    {
      //delay(15);  
    }
            
    if(flip){
      power++;
      if(power >= 250){        
        flip = false;  
      }
    }
    else{
      power--;  
      if(power == 0){
        color++;
        if(color >= 3){
          color = 0;  
        }
        power = 1;
        off_time++;
        if(off_time == 200){
          off_time = 0;
          flip = true;  
        }
      }
    }
    switch(color){
      case 0:
        leds.setColorRGB(0, power, power, 0); 
        break;
      case 1:
        leds.setColorRGB(0, 0, power, power ); 
        break;
      case 2:
        leds.setColorRGB(0, power, 0, power); 
        break;
      default:        
        break;
    }
     
  }
}
void colorWheel()
{
  static int i = 0;
  i++;

  if(i == 1){
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  }  
  if(i == 2){
    colorWipe(strip.Color(0, 255, 0), 50); // Green
  }
  if(i == 3){
    i = 0;
    colorWipe(strip.Color(0, 0, 255), 50); //  
  }  
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void colorWheel1()
{
  static int i = 0;
  i++;

  if(i == 3){
    colorWipe1(strip1.Color(255, 0, 0), 50); // Red
  }  
  if(i == 1){
    colorWipe1(strip1.Color(0, 255, 0), 50); // Green
  }
  if(i == 2){
    i = 0;
    colorWipe1(strip1.Color(0, 0, 255), 50); //  
  }  
}
// Fill the dots one after the other with a color
void colorWipe1(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
  }
  strip1.show();
}
