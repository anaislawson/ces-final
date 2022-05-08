#include <ESP32Servo.h>
#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
#define LEDS_COUNT 130 // The number of led
#define LEDS_PIN 2 // define the pin connected to the Freenove 8 led strip
#define CHANNEL 0 // RMT channel


#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour

using std::cout; using std::cin;
using std::endl; using std::string;
using std::copy;

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

u8 m_color[5][3] = {{0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 30;
int weatherIndex = 0;
int opencount = 0;
int potVal = 0;
bool flag = false;
int outPorts[] = {15, 27, 26, 25};
int indexVal = 0;
int count = 0;
char* people[6] = {"Anais","Sahory","Andre", "Mark", "Gen", "Kennedi"};
int pirPin = 17;                 // PIR Out pin 
int pirStat = 0;                   // PIR status
int posVal = 0;    // variable to store the servo position
int servoPin = 13; // Servo motor pin
char* nameinfo = people[0];
Servo myservoOne;
uint16_t blue = tft.color565(127, 222, 255);
std::map<char*, char*> sunny = {{"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "yes",},
                                {"Mark", "yes",},
                                {"Gen", "yes",},
                                {"Kennedi", "yes"},
                                }; 

std::map<char*, char*> rain = {{"Anais", "no",},
                                {"Sahory", "yes",},
                                {"Andre", "no",},
                                {"Mark", "no",},
                                {"Gen", "no",},
                                {"Kennedi", "no"},
                                }; 
                                

std::map<char*, char*> snow = {{"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "yes",},
                                {"Mark", "no",},
                                {"Gen", "yes",},
                                {"Kennedi", "no"},
                                }; 

std::map<char*, char*> cloudy = {{"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "no",},
                                {"Mark", "yes",},
                                {"Gen", "yes",},
                                {"Kennedi", "yes"},
                                };  
                                
//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    Serial.println("rotate");
    moveOneStep(dir); // Rotate a step
    potVal = analogRead(12);
    Serial.println(potVal);
    pirStat = digitalRead(pirPin); 
    motionDetect(pirStat);
    if(potVal > 1000){
      break;
    } 
    delay(constrain(ms,3,20));        // Control the speed
  }
}

void motionDetect(int pirStat) {
    if (pirStat == HIGH && opencount == 0) {            // if motion detected
    delay(3000);
    Serial.println("Hey I got you in motion!!!");
    if (weatherIndex == 1){
      char* ans = sunny[nameinfo];
      if (ans == "yes"){
        indexVal = random(6);
        nameinfo = people[indexVal];
        openDoor();
        opencount +=1;
        delay(3000);
      }
    }
    else if (weatherIndex == 2){
      char* ans = rain[nameinfo]; 
      if (ans == "yes"){
        indexVal = random(6);
        nameinfo = people[indexVal];
        openDoor();
        opencount +=1;
        delay(3000);
      }
    }
    else if (weatherIndex == 3){
      char* ans = snow[nameinfo];  
      if (ans == "yes"){
        indexVal = random(6);
        nameinfo = people[indexVal];
        openDoor();
        opencount +=1;
        delay(3000);
      }
    }
    else if (weatherIndex == 4){
      char* ans = cloudy[nameinfo];   
      if (ans == "yes"){
        indexVal = random(6);
        nameinfo = people[indexVal];
        openDoor();
        opencount +=1;
        delay(3000);
      }
    }
  } 
  
}
void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) {  // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {      // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

void moveAround(bool dir, int turns, byte ms){
  for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}
void moveAngle(bool dir, int angle, byte ms){
  moveSteps(dir,(angle*32*64/360),ms);
}

void openDoor() {
  //SERVO MOTOR
  for (posVal = 90; posVal >= 20; posVal -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOne.write(posVal);       // tell servo to go to position in variable 'pos'
      //myservoTwo.write(posVal);       // tell servo to go to position in variable 'pos'
      delay(30);                   // waits 15ms for the servo to reach the position
    }
  for (posVal = 20; posVal <= 90; posVal += 1) { // goes from 180 degrees to 0 degrees
    myservoOne.write(posVal);       // tell servo to go to position in variable 'pos'
    //myservoTwo.write(posVal);       // tell servo to go to position in variable 'pos'
    delay(30);                   // waits 15ms for the servo to reach the position
  }  
}
void setup() {

  myservoOne.setPeriodHertz(50);           // standard 50 hz servo
  myservoOne.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo objec
  pinMode(pirPin, INPUT);
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  strip.begin();
  strip.setBrightness(10);
}

void loop() {
 
  potVal = analogRead(12);
  Serial.println(potVal);
  //change weather
  if (potVal < 1000 and potVal > 100){
    weatherIndex = 1;
    //Should only rotate if there is "sunny"  
    // Rotate a full turn
    while(true){ 
      //Serial.println("Hey I got you insun!!!");
      pirStat = digitalRead(pirPin); 
      motionDetect(pirStat);
      moveSteps(true, 32 * 64, 3);
      potVal = analogRead(12);
      Serial.println(potVal);
   
      if(potVal > 1000){
        opencount = 0;
        break;
      }    
      
    }

    
    //sun
  }
  if (potVal < 2000 and potVal > 1000){
    weatherIndex = 2;
    //opencount = 0;
      //rain
    while(true){
      pirStat = digitalRead(pirPin); 
      motionDetect(pirStat);
      for (int i = 4; i < 77; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[0][0], m_color[0][1], m_color[0][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        
        if(potVal > 2000 or potVal < 1000){   
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        }   
      }
      if(flag){
        flag = false;
        opencount = 0;
        break; 
      }

      for (int i = 4; i < 77; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[2][0], m_color[2][1], m_color[2][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        if(potVal > 2000 or potVal < 1000){
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        }   
      }
      if(flag){
        flag =false;
        opencount = 0;
        break; 
      }
      potVal = analogRead(12);
      Serial.println(potVal);
      if(potVal > 2000 or potVal < 1000 or flag == true){
        
        strip.setAllLedsColorData(0, 0, 0);
        strip.show();
        flag = false;
        opencount = 0;
        break;
      } 
    }
     
  }
  if (potVal < 3000 and potVal > 2000){
    weatherIndex = 3;
    //opencount = 0;
    //snow
    while(true){
      pirStat = digitalRead(pirPin); 
      motionDetect(pirStat);
      for (int i = 4; i < 77; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[1][0], m_color[1][1], m_color[1][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        if(potVal > 3000 or potVal < 2000){
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        } 
      }
      if(flag){
        flag =false;
        opencount = 0;
        break; 
      }
      for (int i = 4; i < 77; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[2][0], m_color[2][1], m_color[2][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        if(potVal > 3000 or potVal < 2000){
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        }   
      }
      if(flag){
        flag =false;
        opencount = 0;
        break; 
      }
      potVal = analogRead(12);
      Serial.println(potVal);
     
      if(potVal > 3000 or potVal < 2000 or flag == true){
        
        strip.setAllLedsColorData(0, 0, 0);
        strip.show();
        flag = false;
        opencount = 0;
        break;
      }  
    }
    
    
  }
  if (potVal > 3000){
    
    weatherIndex = 4;
    //cloudy
    while(true){
      pirStat = digitalRead(pirPin); 
      motionDetect(pirStat);
      for (int i = 93; i < 127; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[1][0], m_color[1][1], m_color[1][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        if(potVal < 3000){
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        } 
      }
      if(flag){
        flag =false;
        opencount = 0;
        break; 
      }
      for (int i = 93; i < 127; i++) {
        pirStat = digitalRead(pirPin); 
        motionDetect(pirStat);
        strip.setLedColorData(i, m_color[2][0], m_color[2][1], m_color[2][2]);
        strip.show();
        delay(delayval);
        potVal = analogRead(12);
        Serial.println(potVal);
        if(potVal < 3000){
          strip.setAllLedsColorData(0, 0, 0);
          strip.show();
          flag = true;
          opencount = 0;
          break;
        }   
      }
      if(flag){
        flag =false;
        opencount = 0;
        break; 
      }
      potVal = analogRead(12);
      Serial.println(potVal);
      
      if(potVal < 3000 and flag == true){
        strip.setAllLedsColorData(0, 0, 0);
        strip.show();
        flag = false;
        opencount = 0;
        break;
      } 
    }
     
  }
  
}
