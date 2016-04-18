#include <Arduino.h>
#include <EventManager.h>

//analog threshold for FSR 
#define threshold 100 
//this program attempts to use an event handler with analog0 is sampled above a threshold. 

EventManager gEM; //event manger object 


// the listener is what handles the event (when analog reads higher than threshold.)
void listener( int event, int analogVal )
{
    //print sampled val on serial 
    Serial.println(analogVal);
}

void setup() {
    Serial.begin( 9600 );
    // Add our listener. The kEventAnalog0 is simply an int that matches EventManager to the listener
    gEM.addListener( EventManager::kEventAnalog0, listener );
}

void loop() {
    int sample =0; //refresh sample 
    // Handle ALL events that are in the queue
    gEM.processAllEvents();
    //sample each analog pin (5 on uno) and add event if above threshold 
    for (int i=0;i<5;i++){
      sample = analogRead(i); 
      if(sample > threshold){
         gEM.queueEvent( EventManager::kEventAnalog0, sample );
      }
    } 
}
