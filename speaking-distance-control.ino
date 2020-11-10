
//*********************************************************************************************************
//     Speaking distance control -- A ESP32 microcontroller measueres the distance to a object with a ultrasonic sensor,
//     displays it on a OLED I2C display and give audio announcements by speech samples.
//*********************************************************************************************************
//
// first release on 10/2020
// Version 001 , Nov.10 2020
//


// THE SOFTWARE IS PROVIDED "AS IS" FOR PRIVATE USE ONLY, IT IS NOT FOR COMMERCIAL USE IN WHOLE OR PART OR CONCEPT.
// FOR PERSONAL USE IT IS SUPPLIED WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR
// OR COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//
//

// system libraries
#include "Arduino.h"
#include "XT_DAC_Audio.h";
#include "HCSR04.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h


#include "say_10.h"; //Load the sound samples from flash fs of the controller
#include "say_20.h"
#include "say_100.h"
XT_Wav_Class SpeechSample(say_10_wav);     // create an object of type XT_Wav_Class that is used by 
                                      // the dac audio class (below), passing wav data as parameter.
                                      
XT_DAC_Audio_Class DacAudio(25,0);    // Create the main player class object. 
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0


// Digital I/O used

int triggerPin = 5;    // utrasonic-senor trigger pin
int echoPin = 18;        // utrasonic-senor echo pin
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);



boolean is_playing=false;          // flag is set when a mp3 sample is playing
boolean distance_change=false;      // The distance of the object before ultrasonic sensor has changed
double  min_distance=10;             // Minimum distance (cm) that the meter detecs
int     min_detect_time=50;   
double distance1;
double distance2;
int    sleep_time=1000;    // period before new measure
#define TFT_GREY 0x5AEB // New colour



//**************************************************************************************************
//                                           S E T U P                                             *
//**************************************************************************************************

void setup() {
  Serial.begin(115200);             // Set the serial interface to a baud rate of 115200 
  
  tft.init();                       // Initialize the display
  tft.setRotation(1);
}




//**************************************************************************************************
//                                           E V E N T S                                           *
//**************************************************************************************************


int DistanceChange() // Every 100 miliseconds, do a measurement using the sensor and print the distance in centimeters.
{
    distance1 = distanceSensor.measureDistanceCm();
    if (distance1 >= min_distance) { 
       delay(min_detect_time);
       distance2 = distanceSensor.measureDistanceCm();
       float diff_dist = distance1 - distance2;
       diff_dist = abs(diff_dist);
       //Serial.println(diff_dist);
       if (diff_dist <= min_distance) {    //Check if the obbject has moved)
          distance_change=false;
          //Serial.println("No distance change detected");
          }
    }
    else { 
    distance_change=true;
   // Serial.println("Distance change");
    }
return distance_change;
}


//**************************************************************************************************
//                                            L O O PS                                            *
//**************************************************************************************************



void PlaySample() {
  is_playing=true;
  DacAudio.FillBuffer();                     // Fill the sound buffer with data
  if(SpeechSample.Playing==false)       // if no sample is currently played
    DacAudio.Play(&SpeechSample);       // play it.
    is_playing=false;
}


void UpdateDisplay() {
    tft.fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
   tft.print("Distance to object: ");tft.println(distance2);
}

void loop() {  
   if(is_playing=false) 
       if (  (DistanceChange()) )         // check for distance changes
          Serial.print("Distance to object: ");Serial.println(distance2);
         // delay(sleep_time);
          PlaySample();
          UpdateDisplay(); 
          // delay(sleep_time);          
   
}
   
