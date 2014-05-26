#include "FastLED.h"

// Data pin that led data will be written out over
#define DATA_PIN_ONE   11    // 38 leds, starting offset = 0 
#define DATA_PIN_TWO   10    // 38 leds, starting offset = 38
#define DATA_PIN_THREE  9    // 38 leds, starting offset = 76
#define DATA_PIN_FOUR  12    // 47 leds, starting offset = 114
#define DATA_PIN_FIVE  13    // 28 leds, starting offset = 161

#define NUM_LEDS 38 + 38 + 38 + 47 + 28 
CRGB leds[NUM_LEDS];

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(1000);
  
  // Add strips 
  FastLED.addLeds<WS2811, DATA_PIN_ONE>  (leds,   0, 38);
  FastLED.addLeds<WS2811, DATA_PIN_TWO>  (leds,  38, 38);
  FastLED.addLeds<WS2811, DATA_PIN_THREE>(leds,  76, 38);
  FastLED.addLeds<WS2811, DATA_PIN_FOUR> (leds, 114, 47);
  FastLED.addLeds<WS2811, DATA_PIN_FIVE> (leds, 161, 28);        

  // Other types of stips 
  // WS2811, WS2811_400, NEOPIXEL
  
}

CRGB GetRandomColor() {
  switch( random( 0, 5 ) ) {
    case 0: 
      return CRGB( random( 0, 255), 0, 0 );     
    case 1: 
      return CRGB( 0, random( 0, 255), 0 );     
    case 2: 
      return CRGB( 0,0, random( 0, 255) );            
    case 3: 
      return CRGB( 0,random( 0, 255), random( 0, 255) );            
    case 4: 
      return CRGB( random( 0, 255),0, random( 0, 255) );            
    case 5: 
      return CRGB( random( 0, 255), random( 0, 255), 0 );            
  }
  
  return CRGB( random( 0, 255), random( 0, 255), random( 0, 255) ); 
}

void SolidColor( CRGB color ) {  
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
     leds[i] = color; 
  }  
  FastLED.show();
}

void GrowAndFade( CRGB color, int delayCount = 0 ) {
  // growing/receeding bars
  memset(leds, 0, NUM_LEDS * 3);
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = color; 
    FastLED.show();
    delay( delayCount ) ;
  }
  for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
    leds[i] = CRGB( 0, 0, 0);
    FastLED.show();
    delay(delayCount/2);
  }
}

void TopAndBottom( CRGB top, CRGB bottom) {
  // growing/receeding bars
  memset(leds, 0, NUM_LEDS * 3);
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = bottom; 
    leds[NUM_LEDS-1-i] = top; 
    FastLED.show();
  }
} 

void Snake( CRGB color, int delayCount = 20 ) {
  for(int i = 0 ; i < NUM_LEDS-3; i++ ) {
    memset(leds, 0, i * 3);
    
    leds[i] = color; 
    leds[i+1] = color; 
    leds[i+2] = color; 
    FastLED.show();
    delay(delayCount);
  }  
  
  memset(leds, 0, NUM_LEDS * 3);
}


void RandomFlashers( ) {
   
  // Reset all the leds back to black 
  memset(leds, 0, NUM_LEDS * 3);
  
  // Select x amount of leds 
  int randomLED = random( 0, NUM_LEDS-1) ;   
  for( int offset = 0 ; offset < 25 ; offset ++ ) { 
    if( offset % 2 == 0 ) { 
      leds[ randomLED ] = CRGB( random( 0, 255), random( 0, 255), random( 0, 255) ) ;  
    } else { 
      leds[ randomLED ] = CRGB( 0,0,0 ) ;  
    }
    FastLED.show();
    delay( 20 );
  }
}

void RandomFireFlies( ) {
   
  // Reset all the leds back to black 
  memset(leds, 0, NUM_LEDS * 3);
  
  int steps = 100 ; 
  int randomLED = random( 0, NUM_LEDS-1) ;   
  
  // Fast up 
  for( int offset = 0 ; offset < steps /2  ; offset ++ ) { 
    leds[ randomLED ] = CRGB( map( offset, 0, steps, 0, 255) , 0, 0 ) ;  
    FastLED.show();    
  }
  delay( 20 );
  
  // Slow decay 
  for( int offset = steps ; offset > 0  ; offset -- ) { 
    leds[ randomLED ] = CRGB( map( offset, 0, steps, 0, 255) , 0, 0 ) ;  
    FastLED.show();    
  }
  delay( 20 );
  
  memset(leds, 0, NUM_LEDS * 3);
}

void FullRandom() {
    leds[ random( 0, NUM_LEDS-1) ] = GetRandomColor() ; 
    FastLED.show();
}
  
void PartialRandom() {
  
  if( random(0, 3) == 0 ) {
    // randomly set one on 
    FullRandom(); 
  } else {
    // Randomly set one to black 
    leds[ random( 0, NUM_LEDS-1) ] = CRGB(0,0,0) ; 
    FastLED.show();
  }
}
 
 
void checkerboard()
{
  for( int offset = 0 ; offset < NUM_LEDS ; offset++ ) {  
    if( offset % 2 == 0 ) { 
      leds[ offset ] = CRGB(255,0,0) ; 
    } else {
      leds[ offset ] = CRGB(0,0,255) ; 
    }
  }
  FastLED.show();
}

void colorWheel() {
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255)); 
}


void loop() { 
//  memset(leds, 0, NUM_LEDS * 3);

  colorWheel(); 
   
  return ; 
  /*
  colorWheel(); 
  checkerboard();
  SolidColor( CRGB(255,0,0) ) ;   
  
  
  for( int offset = 0 ; offset < 5 ; offset++ ) {  
    TopAndBottom( GetRandomColor(), GetRandomColor() );
  }
  memset(leds, 0, NUM_LEDS * 3);
  
  for( int offset = 0 ; offset < 5 ; offset++ ) {  
    GrowAndFade( GetRandomColor() ) ;
  }
  // GrowAndFade( GetRandomColor(), 20 ) ;
  memset(leds, 0, NUM_LEDS * 3);

  for( int offset = 0 ; offset < 5 ; offset++ ) {  
    Snake( GetRandomColor() );
  }
  // Snake( GetRandomColor(), 35 );
  memset(leds, 0, NUM_LEDS * 3);
  
  for( int offset = 0 ; offset < 20 ; offset++ ) {  
    RandomFlashers(); 
  }
  memset(leds, 0, NUM_LEDS * 3);
  
  for( int offset = 0 ; offset < 20 ; offset++ ) {  
    RandomFireFlies();
  }
  memset(leds, 0, NUM_LEDS * 3);
  
  for( int offset = 0 ; offset < 500 ; offset++ ) {  
    FullRandom();
  }
  memset(leds, 0, NUM_LEDS * 3);
  
  for( int offset = 0 ; offset < 500 ; offset++ ) {  
    PartialRandom();   
  }
  memset(leds, 0, NUM_LEDS * 3);
  
  return; 
  */
    /*
  // one at a time
  for(int j = 0; j < 3; j++) { 
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      memset(leds, 0, NUM_LEDS * 3);
      switch(j) { 
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      FastLED.show();
      // delay(100);
    }
  }

  // growing/receeding bars
  for(int j = 0; j < 3; j++) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      switch(j) { 
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      FastLED.show();
      // delay(100);
    }
    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
      switch(j) { 
        case 0: leds[i].r = 0; break;
        case 1: leds[i].g = 0; break;
        case 2: leds[i].b = 0; break;
      }
      FastSPI_LED.show();
      delay(1);
    }
  }
*/
  // Fade in/fade out
  for(int j = 0; j < 3; j++ ) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int k = 0; k < 256; k++) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
    }
    for(int k = 255; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
    }
  }
  
  
}