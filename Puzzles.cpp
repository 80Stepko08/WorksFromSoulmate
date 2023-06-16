#define PRows 4
#define PCols 4
byte puzzle[PCols][PRows];
byte tmpp;
byte z_dot[2];
byte etap;
int8_t move[2];
int8_t shift[2] = {0,0};
bool XorY;

void draw_square(byte x1, byte y1, byte x2, byte y2, byte col) {
  for (byte x = x1; x < x2; x++) {
    for (byte y = y1; y < y2; y++) {
      if(col == 0){leds[XY(x, y)] = CRGB(0,0,0);}
      else if ((x == x1 || x == x2 - 1) || (y == y1 || y == y2 - 1))
        leds[XY(x, y)] = ColorFromPalette(ForestColors_p, col - 16);
      else leds[XY(x, y)] = ColorFromPalette(ForestColors_p, col);
    }
  }
}

bool setup = true;
void draw() {
  if (setup) {
    etap = 0;
    for (byte x = 0; x < PCols; x++) {
      for (byte y = 0; y < PRows; y++) { puzzle[x][y] = random8(16, 255); }
    }
    z_dot[0] = random(0, PCols);
    z_dot[1] = random(0, PRows);
    puzzle[z_dot[0]][z_dot[1]] = 0;
    setup = false;
  }
  
  for (byte x = 0; x < PCols; x++) {
    for (byte y = 0; y < PRows; y++) {
      draw_square(x * LED_COLS / PCols, y * LED_ROWS / PRows, x * LED_COLS / PCols + (LED_COLS / PCols), y * LED_ROWS / PRows + (LED_ROWS / PRows), puzzle[x][y]);
    }
  }
  switch (etap) {
    case 0:
        XorY = !XorY;
      if(XorY){
          if (z_dot[0] == PCols - 1)
            move[0] = -1;
          else if (z_dot[0] == 0) move[0] = 1;
          else move[0] = (move[0] == 0) ? (random() % 2) * 2 - 1 : move[0];
         }else{
          if (z_dot[1] == PRows - 1)
            move[1] = -1;
          else if (z_dot[1] == 0) move[1] = 1;
          else move[1] = (move[1] == 0) ? (random() % 2) * 2 - 1 : move[1];
      }
      move[(XorY)? 1 : 0] = 0;
      etap = 1;
      break;
    case 1:
      tmpp = puzzle[z_dot[0] + move[0]][z_dot[1] + move[1]];
      puzzle[z_dot[0] + move[0]][z_dot[1] + move[1]] = 0;
      etap = 2;
      break;
    case 2:
      draw_square((z_dot[0] + move[0]) * LED_COLS / PCols + shift[0], (z_dot[1] + move[1]) * LED_COLS / PRows + shift[1], ((z_dot[0] + move[0]) * LED_COLS / PCols) + (LED_COLS / PCols) + shift[0], ((z_dot[1] + move[1]) * LED_COLS / PRows) + (LED_ROWS / PRows) + shift[1], tmpp);
      shift[0] -= move[0];
      shift[1] -= move[1];
      if ((fabs(shift[0]) >= LED_COLS / PCols) || (fabs(shift[1]) >= LED_ROWS / PRows)) {
        shift[0] = 0;
        shift[1] = 0;
        puzzle[z_dot[0]][z_dot[1]] = tmpp;
        etap = 3;}
      break;
    case 3:
      z_dot[0] += move[0];
      z_dot[1] += move[1];
      etap = 0;
      break;
  }
}