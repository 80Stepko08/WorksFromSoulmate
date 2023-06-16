void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
  const CRGB & color) {
  int8_t deltaX = abs(x2 - x1);
  int8_t deltaY = abs(y2 - y1);
  int8_t signX = x1 < x2 ? 1 : -1;
  int8_t signY = y1 < y2 ? 1 : -1;
  int8_t error = deltaX - deltaY;
  
  leds[XY(x2, y2)] = color;
  while (x1 != x2 || y1 != y2) {
    leds[XY(x1, y1)] = color;
    int8_t error2 = error * 2;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
}

void draw() {
  fadeToBlackBy(leds, NUM_LEDS, 32);
for(byte x = 0; x < LED_COLS; x++){
  drawLine(x,LED_ROWS/8,x,map(inoise8(x*80),0,255,LED_ROWS/8,LED_ROWS-1),CHSV(20,100,100));
}
  for(byte x = 0; x < LED_COLS; x++){
    for(byte y = 0; y < LED_ROWS/8; y++){
      leds[XY(x,y)]=CHSV(20,128,255-32*y);
    }
  }
  for (int i = (LED_COLS*LED_ROWS)/16; i < NUM_LEDS; i++) {
    leds[i] += CHSV(0, 0, inoise8(i * 20, millis()/8)/4);
  } 
 blur2d(leds, LED_COLS, LED_ROWS, 16);
}