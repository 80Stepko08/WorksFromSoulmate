//RadialNuclearNoise
//Stepko and Sutaburosu
//15/03/23
bool setupm = 1;
const uint8_t C_X = LED_COLS / 2;
const uint8_t C_Y = LED_ROWS / 2;
const uint8_t mapp = 255 / LED_COLS;
struct{
  uint8_t angle;
  uint8_t radius;
} rMap[NUM_LEDS];
void draw() {
  FastLED.clear();
  if (setupm) {
    setupm = 0;
    for (int8_t x = -C_X; x < C_X + (LED_COLS % 2); x++) {
      for (int8_t y = -C_Y; y < C_Y + (LED_ROWS % 2); y++) {
        uint16_t coord = XY(x + C_X, y + C_Y);
        rMap[coord].angle = 128 * (atan2(y, x) / PI);
        rMap[coord].radius = hypot(x, y) * mapp; //thanks Sutaburosu
      }
    }
  }
  
  static byte speed = 8;
  static uint16_t t;
  t += speed;
  uint16_t t1 = t / 2;
  for (uint8_t x = 0; x < LED_COLS; x++) {
    for (uint8_t y = 0; y < LED_ROWS; y++) {
      uint16_t coord = XY(x,y);
      uint8_t angle = sin8(t1 / 2 + rMap[coord].angle * 3);
      uint8_t radius = (rMap[coord].radius) * 2 - t;
      uint8_t noise[3] = { inoise8(angle, radius, t1), inoise8(angle, 12032 + t1, radius), inoise8(radius, 120021 + t1, angle) };
      for(uint8_t i = 0; i < 3; i++){
        noise[i] = (noise[i] < 128) ? 0 : constrain((noise[i] - 128) * 3,0,255);
      }
      leds[coord] = CRGB(noise[0], noise[1], noise[2]);
    }
  }
  delay(16);
}