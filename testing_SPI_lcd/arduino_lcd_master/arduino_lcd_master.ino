#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

//this is for the LCD
#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define slave_select1 1 //change slave select pin to 1 for the slave arduino

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

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//pressures for touch screen
#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

//this will tell what to display on LCD 0=don't draw, 1=main menu, 2=free play, 3= guidance mode.
int menu_mode = 0; 

//this function draws the main menu
void main_menu(){
  tft.fillScreen(BLACK);
  //begin by showing user a menu. Two buttons
  tft.fillRect(0, 0, 120, 320, GREEN);
  tft.fillRect(120, 0, 120, 320, BLUE);
  
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.setCursor(50,50);
  //set rotation so text is in landscape mode
  tft.setRotation(1);
  tft.print("Free Play");
  tft.setCursor(5,150);
  tft.print("Guidance Mode");

  while(1){
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        if (p.x < 120){
          menu_mode = 2;
          break;
        }else if (p.x > 120){
            //else switch to guidance mode
          menu_mode = 3;
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
    while(1){
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    TSPoint p = ts.getPoint();
      // if user touches screen above a certain pressure, then register touch
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //if the top half of screen is pressed during main menu then switch to free play
        menu_mode = 1;
        break;
      } 
   }
}

void guidance_mode(){
  tft.reset();
  tft.fillScreen(CYAN);
  back_button();
}


void setup (void)
{
  pinMode(slave_select1, OUTPUT);
  digitalWrite(slave_select1, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);

//the following is for the LCD
  tft.reset();
  uint16_t identifier = 0x9341;
  tft.begin(identifier);

  //draw main menu
  main_menu(); 
  
}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(slave_select1, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Hello, world!\n" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(slave_select1, HIGH);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  //these series of if statements will draw the menu when a change is needed
  if (menu_mode == 1){
    main_menu();
    menu_mode = 0;
  }else if(menu_mode == 2){
    free_play();
    menu_mode = 0;
  }else if(menu_mode == 3){
    guidance_mode();
    menu_mode = 0;
  }

  delay (200);  // 1 seconds delay 
}  // end of loop
