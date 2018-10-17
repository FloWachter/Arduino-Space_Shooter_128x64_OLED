#include <Adafruit_SSD1306.h>
#include "fire.h"

extern Adafruit_SSD1306 display;

Bullet fire[MAX_BULLETS];

void init_bullet() {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    fire[i].x = 20;
    fire[i].y = 0;
    fire[i].fired = false;
  }    
}

void draw_bullet() {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if(fire[i].fired == true){
      display.drawPixel(fire[i].x, fire[i].y, WHITE); 
    }
  }    
}

void move_bullet() {   
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if(fire[i].fired == true){
      fire[i].x += 4; 
    }
    if (fire[i].x < 0) {
      fire[i].x = 20;
      fire[i].fired = false;
    }
  }
}

void trigger_bullet(int shipPos) {
  for (uint8_t i = 0; i < MAX_BULLETS; i++) {
    if(fire[i].fired == false){
        fire[i].y = shipPos + 5;
        fire[i].fired = true;
        break;
    }
  }
}


