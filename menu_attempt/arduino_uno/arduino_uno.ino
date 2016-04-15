#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

/*
 * This LCD is 240x320
 * The identifier for this LCD is 
 */

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//initilzie touch screen
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//pressures for touch screen
#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

//this will tell what to display on LCD 0=Nothing, 1=tutorial, 2=main menu, 3=free play, 4=guidance mode.
int menu_mode = 0; 

//This function will be the introduction screen.
void intro_screen(){
  tft.fillScreen(MAGENTA);
  //These two buttons will be to ask user if they want to see the tutorial
  tft.fillRect(0,140,160,100,GREEN); //yes
  tft.fillRect(160,140,160,100,RED); //no
  //this is the welcome text
  tft.setTextColor(BLACK);
  tft.setTextSize(6);
  tft.setCursor(10,10);
  tft.println("Welcome!");
  tft.setTextSize(3);
  tft.println("Would you like");
  tft.println("to view ");
  tft.println("the tutorial?");
  tft.setTextSize(4);
  tft.setCursor(50,180);
  tft.print("Yes");
  tft.setCursor(220,180);
  tft.print("No");
//begin touch screen for yes or no
    while(1){
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //go to tutorial if yes is pressed, otherwise go straight to menu 
        if (p.x > 140 && p.y < 160){
          //go to tutorial
          menu_mode = 1;
          break;
        }else if (p.x > 140 && p.y > 160){
            //or go straight to menu 
          menu_mode = 2;
          break;
        }
      } 
   }
}

//this function is the tutorial screen
void tutorial(){
  tft.fillScreen(CYAN);
  //make main menu button 
  tft.fillRect(0,140,320,100,GREEN); //yes
  tft.setCursor(20,160);
  tft.setTextSize(4);
  tft.print("Main Menu");
  while(1){
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        if (p.x > 120){
          menu_mode = 2;
          break;
        }
      } 
   }
}

//this function draws the main menu
void main_menu(){
  tft.fillScreen(BLACK);
  //begin by showing user a menu. Two buttons
  tft.fillRect(0, 0, 320, 120, GREEN);
  tft.fillRect(0, 120, 320, 120, BLUE);
  
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.setCursor(50,50);
  tft.print("Free Play");
  tft.setCursor(5,150);
  tft.print("Guidance Mode");

  while(1){
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        if (p.x < 120){
          menu_mode = 3;
          break;
        }else if (p.x > 120){
            //else switch to guidance mode
          menu_mode = 4;
          break;
        }
      } 
   }
}

void back_button(){
  //this creates a back button to go to main menu
  tft.fillRect(0, 0, 50, 20, RED);
  tft.setCursor(3,3);
  tft.setTextSize(2);
  tft.print("Back");
}

void free_play(){
  tft.fillScreen(BLACK);
  back_button();
  //this is for the back button 
  while(1){
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        if (p.y < 50, p.x < 50){
          menu_mode = 2;
          break;
        }
      } 
   }
}

void guidance_mode(){
  tft.fillScreen(YELLOW);
  back_button();
  while(1){
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        if (p.y < 50, p.x < 50){
          menu_mode = 2;
          break;
        }
      } 
   }
}

void setup(void) {
  tft.reset();
  uint16_t identifier = 0x9341;
  tft.begin(identifier);
  //set rotation so text is in landscape mode
  tft.setRotation(1);

  //draw introduction screen
  intro_screen();
}


void loop()
{
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  //these series of if statements will draw the menu when a change is needed
  if (menu_mode == 1){
    tutorial();
  }else if(menu_mode == 2){
    main_menu();
  }else if(menu_mode == 3){
    free_play();
  }else if(menu_mode == 4){
    guidance_mode();
  }
}












