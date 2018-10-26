#include <Adafruit_SSD1306.h>
#include "meteorites.h"

extern Adafruit_SSD1306 display;

Meteorites meteo[MAX_METEORITES];




void init_meteo() {
  for (uint8_t i = 0; i < MAX_METEORITES; i++) {
    meteo[i].x = random(display.width());
    meteo[i].y = random(display.height());
    meteo[i].vx = random(3) + 1;
  }
}

void move_meteo() {
  for (uint8_t i = 0; i < MAX_METEORITES; i++) {
    meteo[i].x -= meteo[i].vx;
    if (meteo[i].x < 0) {
      meteo[i].x = display.width();
      meteo[i].y = random(display.height());
      meteo[i].vx = random(3) + 1;
    }
  }
}

void draw_meteo() {
  for (uint8_t i = 0; i < MAX_METEORITES; i++) {
    //display.drawPixel(meteo[i].x, meteo[i].y, WHITE);
    static const unsigned char PROGMEM meteo_img[] = {
      0x00,0x00, // ................
      0x3F,0x00, // ..######........
      0x7F,0x80, // .########.......
      0xE7,0x80, // ###..####.......
      0xE7,0x80, // ###..####.......
      0xFF,0x80, // #########.......
      0x7F,0x80, // .########.......
      0x7F,0x80, // .########.......
      0x3F,0x00, // ..######........
      0x3E,0x00 // ..#####.........
    };
  display.drawBitmap(meteo[i].x, meteo[i].y,meteo_img, 10, 10, 1);
  }
}

