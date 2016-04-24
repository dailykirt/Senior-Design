#include <StopWatch.h>
#include <Thread.h>
#include <ThreadController.h>
#include <EventManager.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <MIDI.h>

//touch screen declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
//end touch screen delcarations ~~~~~~~~~~~~~~~~~~~~~~~


//the following deals with the touch screen threads~~~~~~~~~~~~~~~~~~~~~~
// Create a new Class, called touchThread, that inherits from Thread
class touchThread: public Thread
{
public:
  TSPoint p;
  //this will tell what is shown on LCD 0=Nothing, 1=tutorial, 2=main menu, 3=free play, 4=guidance mode.
  int menu_mode = 0; 
  bool recently_drawn = true;
  //overloaded run method that reads from touch screen
  void run(){
    //get point then map cordinates to touch screen 
     p = ts.getPoint();
     //if ts is touched then map coordinates 
     if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        //for each type of menu, different touch patterns do different things 
        //touch pattern for intro
        if (menu_mode == 0){
            if (p.x > 140 && p.y < 160){
            menu_mode = 1;
            recently_drawn = false;      
          }else if (p.x > 140 && p.y > 160){
            //or go straight to menu 
            menu_mode = 2;
            recently_drawn = false;
          }
        }else if(menu_mode == 1){
          //for tutorial 
          if (p.x > 120){
          menu_mode = 2;
          recently_drawn = false;
          }
        }else if(menu_mode == 2){
          //for main menu 
          if (p.x < 120){
            menu_mode = 3;
            recently_drawn = false;
          }else if (p.x > 120){
            //else switch to guidance mode
            menu_mode = 4;
            recently_drawn = false;
          }
        }else if(menu_mode == 3 || menu_mode == 4){
          //back button 
            if (p.y < 50, p.x < 50){
            menu_mode = 2;
            recently_drawn = false;
            }
        }
     }
     runned();
  }
};

//create a touchThread
touchThread tsThread = touchThread();
//end touch screen threads~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//dealing with MIDI~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//creating note object that stores duration 
class midiNote{
public:
//a notePitch from 1-12
  int notePitch;
  unsigned int actual_time=0;
  float normalized_time=0.0;
  StopWatch sw;
  //if an incoming note matches the pitch start a timer start timer
  void setTimer(){
      sw.start();
  }
  void stopTimer(){
     sw.stop();
     actual_time = sw.elapsed();
  }
};

MIDI_CREATE_DEFAULT_INSTANCE();
midiNote midiDataArr[12];

// When MIDI in is detected the following function will set a timer to find note duration
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (velocity != 0){
      int noteFound = pitch % 12;
      midiDataArr[noteFound].setTimer();      
  }
}
//then stop timer and update note duration
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  if (velocity == 0){
      int noteFound = pitch % 12;
      midiDataArr[noteFound].stopTimer();
  }
}

//end MIDI~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Algorithim Thread~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Thread algThread = Thread(); //make new thread
boolean key_change = true; //used to only draw when key changes
//first 12 is major, last 12 is minor
//float major_chroma[12] = {0.125,0.0,0.0,0.25,0.0,0.125,0.0,0.125,0.25,0.0,0.0,0.125};
float major_chroma[12] = {1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float minor_chroma[12] = {0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float min_ecludian = 9999.0;
unsigned long total_duration = 0; //in ms 
//the following selects which key is being predicted. will be form 0-23
int predicted_key=0;
float confidence = 0.0;
void algorithim_callback(){
  int index;
  //first update total duration 
  unsigned long duration_sum=0;
  float current_euclidean = 0.0;
  //sum up all durations and update total_duration 
  for (int i=0;i<12;i++){
    duration_sum = duration_sum + midiDataArr[i].actual_time;
  }
  total_duration = duration_sum;
  
  //normalize data
  for (int i=0; i<12;i++){
     if(total_duration != 0){
        midiDataArr[i].normalized_time = (float)midiDataArr[i].actual_time / (float)total_duration;
     }
  }
  
  //find ecludian distance max first for minor
  for (int i=0;  i<12; i++){
      for (int j=0;j<12;j++){
         index = i + j;
         if (index >= 12){
          index = index - 12;
         }
         current_euclidean = current_euclidean + pow((midiDataArr[j].normalized_time - major_chroma[index]),2);
      }
      current_euclidean = sqrt(current_euclidean);
      if(current_euclidean < min_ecludian){
        min_ecludian = current_euclidean;
        predicted_key = i;
      }
      current_euclidean = 0; //refresh current_euclidean
  }

    //then minor
  for (int i=0;  i<12; i++){
      for (int j=0;j<12;j++){
         index = i + j;
         if (index >= 12){
          index = index - 12;
         }
         current_euclidean = current_euclidean + sqrt(pow((midiDataArr[j].normalized_time - minor_chroma[index]),2));
      }
      if(current_euclidean < min_ecludian){
        min_ecludian = current_euclidean;
        predicted_key = i + 12;
      }
      current_euclidean = 0; //refresh current_euclidean
  }
  
  confidence = 1 - min_ecludian;
  key_change = true; //if key changed set this true 
}
//end algorithim ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//following functions are for the menu astetics ~~~~~~~~~~~~~~~~~~~~~
//draws introduction screen 
void draw_intro(){
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
}

//draws tutorial screen 
void draw_tutorial(){
  tft.fillScreen(CYAN);
  //make main menu button 
  tft.fillRect(0,140,320,100,GREEN); //yes
  tft.setCursor(20,160);
  tft.setTextSize(4);
  tft.print("Main Menu");
}

//this function draws the main menu
void draw_main_menu(){
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
}

void draw_back_button(){
  //this creates a back button to go to main menu
  tft.fillRect(0, 0, 50, 20, RED);
  tft.setCursor(3,3);
  tft.setTextSize(2);
  tft.print("Back");
  //clear old data 
  for(int i=0;i<12;i++){
    midiDataArr[i].actual_time = 0;
    midiDataArr[i].normalized_time = 0;
  }
  min_ecludian = 9999.0;
  total_duration = 0; 
  predicted_key= 0;
  confidence = 0.0;
}

void draw_free_play(){
  tft.fillScreen(BLACK);
  draw_back_button();
  tft.setTextColor(WHITE);
  tft.setCursor(20,60);
  tft.setTextSize(3);
  tft.println("Your Predicted");
  tft.println("");
  tft.println("Key:");
  tft.println("");
  tft.println("Correct:");
}

void draw_guidance_mode(){
  tft.fillScreen(YELLOW);
  draw_back_button();
}

//remember to change type to unsigned long for time.
void draw_predictedKey(int keyVal){
    tft.setCursor(75,110);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.fillRect(75, 110, 80, 30, BLACK);
    if(total_duration == 0){
      tft.print(" ?");
    }else{
      tft.println(keyVal);
    }
}

void draw_confidence(float confidence){
    tft.setCursor(145,160);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.fillRect(140, 160, 80, 30, BLACK);
    if(total_duration == 0){
      tft.print(" ?");
    }else{
      tft.print(confidence);
    }
}
//end of menu astetics~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  tft.reset();
  uint16_t identifier = 0x9341;
  tft.begin(identifier);
  //set rotation so text is in landscape mode
  tft.setRotation(1);
  //draw introduction screen
  draw_intro();
  // Configures thread intervals
  tsThread.setInterval(200);
  algThread.onRun(algorithim_callback);
  algThread.setInterval(4000);
  //configure function incoming MIDI calls 
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library all channels 
  Serial.begin(115200); //inizlize midi over serial 
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  //set pitches to midi data 
  for(int i=0;i<12;i++){
    midiDataArr[i].notePitch = i;
  }
}

void loop() {
  MIDI.read(); //check for MIDI In
  //checks if threads need to be run then run all 
  if(tsThread.shouldRun()){
      tsThread.run();
  }
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
 
  //the following redraws menu if thread detects appropriate touch 
  if (tsThread.recently_drawn == false){
      if ( tsThread.menu_mode == 1){
          draw_tutorial();
      }else if(tsThread.menu_mode == 2){
          draw_main_menu();
      }else if (tsThread.menu_mode == 3){
          draw_free_play();
          draw_back_button();
      }else if (tsThread.menu_mode == 4){
          draw_guidance_mode();
          draw_back_button();
      }
      tsThread.recently_drawn = true;
  }

  //following function updates freedraw screen if a new key is detected 
  if (tsThread.menu_mode == 3 && key_change == true){
    if(algThread.shouldRun()){
        algThread.run();
        draw_predictedKey(predicted_key);
        draw_confidence(confidence);
        //draw_confidence(min_ecludian);
        key_change == false;
        min_ecludian = 9999.0; //refresh 
    }
  }
}




