
/*********************************************************************
  Written by Florian Wachter
  florianwachter.com
  UX Designer & Developer
  
  Graphics created with:
  http://marlinfw.org/tools/u8glib/converter.html
  

*********************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tones.h"
#include "starfield.h"
#include "meteorites.h"
#include "fire.h" 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Global varaibles
uint8_t color = WHITE;
int speakerPin = 8;
int bullet_button = 12;
int buttonState = 0;
int ship_margin = 10;
int amor = 100;
int score = 0;


// ----------------------------------------------------------
// Init Functions
// ----------------------------------------------------------
void init_display() {
  Serial.begin(9600);
  // initialize with the I2C addr 0x3D (for the 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  
  display.display();
  delay(10);
  display.clearDisplay();
}

void init_poti() {
  int poti = A0;
  int potiValue = 0;
  pinMode(poti, INPUT);
}

void init_bullet_button(){
  pinMode(bullet_button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  
}

// ----------------------------------------------------------
// Display Functions
// ----------------------------------------------------------
void display_ship(int pos){
  static const unsigned char PROGMEM spaceShip_img[] = {
  0x78, 0x00, 0x7c, 0x00, 0x30, 0x00, 0x3f, 0x80, 0xfc, 0xc0, 0xfc, 
  0xc0, 0x3f, 0x80, 0x30, 0x00,0x7c, 0x00, 0x78, 0x00 };
  display.drawBitmap(ship_margin, pos,spaceShip_img, 10, 10, 1);
}

int shipPosition(){
  int potiValue = analogRead(A0);
  return map(potiValue, 40, 1024, 0, display.height()-10); 
}

bool fire_bullet() {
  buttonState = digitalRead(bullet_button);
  if (buttonState == !HIGH) {
    tone(speakerPin, NOTE_A5, 100);
    digitalWrite(LED_BUILTIN, HIGH);
    return true;
  }else{
    digitalWrite(LED_BUILTIN, LOW);
    return false;
  }
}

void bullet(bool fire) {
  if( fire == true ){
    trigger_bullet(shipPosition());
  } 
}

void collition_check(int shipPos) {
  // METERIORIT COLLITION
  for (uint8_t i = 0; i < MAX_METEORITES; i++) { 
    if( meteo[i].x < ship_margin + 6 &&  meteo[i].x >= ship_margin ) {
      // in range of x-axses 
      
      if( meteo[i].y < shipPos + 8 &&  meteo[i].y >= shipPos ) {
        // in range of y-axses
        if(amor > 0 ){ 
          tone(speakerPin, NOTE_C2, 100);
          amor --;          
        }else {
          amor = 0;
        }
        meteo[i].visible = false;
      }
    }
  }

  // BULLET COLLITION
  for (uint8_t i_bu = 0; i_bu < MAX_BULLETS; i_bu++) {
    for (uint8_t i_me = 0; i_me < MAX_METEORITES; i_me++) { 
      if (fire[i_bu].x >= meteo[i_me].x && fire[i_bu].x < meteo[i_me].x + 10 && fire[i_bu].fired == true) {
        if (fire[i_bu].y >= meteo[i_me].y && fire[i_bu].y < meteo[i_me].y + 10 ) {
          tone(speakerPin, NOTE_E3, 100);
          meteo[i_me].visible = false;
          fire[i_bu].fired = false;
          score++;
        }
      }
    }
  }
}





void display_lifes(){
static const unsigned char PROGMEM armor_img[] = {
  0xFC, // ######..
  0xFC, // ######..
  0xFC, // ######..
  0xFC, // ######..
  0x78, // .####...
  0x30, // ..##....
};
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(display.width() - 20, 0);
  display.println(amor);
  display.drawBitmap(display.width() - 30, 0, armor_img , 6, 6, 1);
}

void display_score(){
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.println(score);
  
}


// ----------------------------------------------------------
// SETUP
// ----------------------------------------------------------
void setup() {
  init_display();
  init_poti();
  
  init_starfield();
  init_meteo();
  
  init_bullet_button();
  init_bullet();
}



// ----------------------------------------------------------
// LOOP 
// ----------------------------------------------------------
void loop() {
  move_stars();
  draw_stars();
  
  display_ship(shipPosition());
  
  bullet(fire_bullet());

  draw_bullet();
  move_bullet();

  draw_meteo();
  move_meteo();
  
  collition_check(shipPosition());
  display_lifes();
  display_score();

  
  


  
  
  display.display();
  delay(5);
  display.clearDisplay();
}



