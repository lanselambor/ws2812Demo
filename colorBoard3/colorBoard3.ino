#include <ChainableLED.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

//ws2802
#define PIN             6
#define PIN1            5

#define NUMPIXELS      38

uint32_t colorsRed2Blue[12] = {
0xB90E46, 0xD1092E, 0xE80517, 0xFF0000,    
0x5D20A2, 0x741C8B, 0x8B1774, 0xA2135D,   
0x0033FF, 0x172EE8, 0x2E2AD1, 0x4625B9
};

uint32_t colors_Green2Blue[12] = {
0x00FF00, 0x00E817, 0x00D12E, 0x00B946, 
0x00A25D, 0x008B74, 0x00748B, 0x005DA2,
0x0046B9, 0x002ED1, 0x0017E8, 0x0000FF
};

uint32_t colors_Red2Green[12] = {
0xFF0000, 0xE81700, 0xD12E00, 0xB94600, 
0xA25D00, 0x8B7400, 0x748B00, 0x5DA200,
0x46B900, 0x2ED100, 0x17E800, 0x00FF00
};                                  
                                                        
                      
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);


void setup()
{
  strip.begin(); // This initializes the NeoPixel library.
  strip1.begin();
}

void loop()
{    
#if 1  
  colorWheel(&strip, 1);
  colorWheel(&strip1, 0);
  delay(200);
  colorWheel(&strip, 0);
  colorWheel(&strip1, 1);
  delay(700);
  colorWheel(&strip, 2);
  colorWheel(&strip1, 0);
  delay(200);
  colorWheel(&strip, 0);
  colorWheel(&strip1, 2);
  delay(700);
  colorWheel(&strip, 3);
  colorWheel(&strip1, 0);
  delay(200);
  colorWheel(&strip, 0);
  colorWheel(&strip1, 3);
  delay(700);  

  colorWheel(&strip, 0);
  colorWheel(&strip1, 0);
  
  scroll(&strip, 0x00ff0000);
  scroll(&strip1, 0x0000ff00);
#endif

//  action_1(&strip, &strip1, 0x0000ff00, 0x000000ff);
//  action_1(&strip, &strip1, 0x0000ff00, 0x0000ff00);
//  
//  action_1(&strip, &strip1, 0x00ff0000, 0x0000ff00);
//  action_1(&strip, &strip1, 0x0000ff00, 0x0000ff00);
//  
//  action_1(&strip, &strip1, 0x000000ff, 0x00ff0000);
//  action_1(&strip, &strip1, 0x0000ff00, 0x0000ff00);

    action_2(&strip, &strip1, 0x0000ff00, colorsRed2Blue);
    action_2(&strip, &strip1, 0x00ff0000, colors_Green2Blue);
    action_2(&strip, &strip1, 0x000000ff, colors_Red2Green);
}

void colorWheel(Adafruit_NeoPixel *pixel, int color)
{
  //1.red  2.green   3.blue
  if(color == 1){
    colorWipe(pixel, pixel->Color(255, 0, 0)); // Red
  }  
  else if(color == 2){
    colorWipe(pixel, pixel->Color(0, 255, 0)); // Green
  }
  else if(color == 3){
    colorWipe(pixel, pixel->Color(0, 0, 255)); //  
  }  
  else if(color == 0){
    colorWipe(pixel, pixel->Color(0, 0, 0)); //  
  }
}

void colorWipe(Adafruit_NeoPixel *pixel, uint32_t c) {
  for(uint16_t i=0; i<pixel->numPixels(); i++) {
    pixel->setPixelColor(i, c);
  }
  pixel->show();
}

void scroll(Adafruit_NeoPixel *pixel, uint32_t c){
  for(uint16_t i=0; i<pixel->numPixels(); i++) {
    pixel->setPixelColor(i, c);
    pixel->show();
    delay(30);
  } 
}

void action_1(Adafruit_NeoPixel *pixel1, Adafruit_NeoPixel *pixel2, uint32_t c1, uint32_t c2){
  for(uint16_t i=0; i<pixel1->numPixels(); i++) {
    pixel1->setPixelColor(i, c1);
    pixel2->setPixelColor(pixel1->numPixels()-i, c2);
    pixel1->show();
    pixel2->show();
    delay(10);
    pixel1->clear();
    pixel2->clear();
    pixel1->show();
    pixel2->show();    
  }
}

void action_2(Adafruit_NeoPixel *pixel1, Adafruit_NeoPixel *pixel2, uint32_t c1, uint32_t *c2){
  uint16_t i=0; 
  uint32_t color;
    
  for(i=0; i<pixel1->numPixels()/2; i++) {
    pixel1->setPixelColor(i, c1);
    pixel2->setPixelColor(pixel1->numPixels()-i, c1);
    pixel1->show();
    pixel2->show();
    delay(20);
    pixel1->clear();
    pixel2->clear();
    pixel1->show();
    pixel2->show();    
  }
  for(; i<pixel1->numPixels(); i++) {
    pixel1->setPixelColor(i, c2[(map(i, pixel1->numPixels()/2, pixel1->numPixels(), 0, 11))]);
    pixel2->setPixelColor(pixel1->numPixels()-i, c2[(map(i, pixel1->numPixels()/2, pixel1->numPixels(), 0, 11))]);
    pixel1->show();
    pixel2->show();
    delay(20);
    pixel1->clear();
    pixel2->clear();
    pixel1->show();
    pixel2->show();    
  }  
}
