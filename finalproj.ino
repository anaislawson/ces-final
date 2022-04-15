/**********************************************************************
  Filename    : Drive Stepper Motor
  Description : Use ULN2003 to drive the stepper motor.
  Auther      : www.freenove.com
  Modification: 2020/07/11
**********************************************************************/
#include <ESP32Servo.h>
#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <Freenove_WS2812_Lib_for_ESP32.h>

#define LEDS_COUNT 10 // The number of led
#define LEDS_PIN 2 // define the pin connected to the Freenove 8 led strip
#define CHANNEL 0 // RMT channel
using namespace std;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::copy;

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

u8 m_color[5][3] = {{0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 100;

map<string, string> sunny = {"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "yes",},
                                {"Mark", "yes",},
                                {"Gen", "yes",},
                                {"Kennedi", "yes",}}; 

map<string, string> rain = {"Anais", "no",},
                                {"Sahory", "yes",},
                                {"Andre", "no",},
                                {"Mark", "no",},
                                {"Gen", "no",},
                                {"Kennedi", "no",}}; 
                                

map<string, string> snow = {"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "yes",},
                                {"Mark", "no",},
                                {"Gen", "yes",},
                                {"Kennedi", "no",}}; 

map<string, string> cloudy = {{"Anais", "yes",},
                                {"Sahory", "yes",},
                                {"Andre", "no",},
                                {"Mark", "yes",},
                                {"Gen", "yes",},
                                {"Kennedi", "yes",}};                            
// Connect the port of the stepper motor driver
int outPorts[] = {15, 27, 26, 25};
int index = 0;
int count = 0;
int opencount = 0; 
const string people[6] = {"Anais, Sahory, Andre, Mark, Gen, Kennedi"};
//int ledPin = 13;                // LED 
int pirPin = 2;                 // PIR Out pin 
int pirStat = 0;                   // PIR status

void loop(){
 pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println("Hey I got you!!!");
 } 
 else {
   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
 }
} 
Servo myservoOne;  // create servo object to control a servo
Servo myservoTwo;  // create servo object to control a servo

int posVal = 0;    // variable to store the servo position
int servoPin = 15; // Servo motor pin
int weatherIndex = 0;
string name = people[0];
void setup() {
  //motor setup  
  // set pins to output
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
  myservoOne.setPeriodHertz(50);           // standard 50 hz servo
  myservoOne.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object

  myservoTwo.setPeriodHertz(50);           // standard 50 hz servo
  myservoTwo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
  //pinMode(ledPin, OUTPUT);     
  pinMode(pirPin, INPUT);     
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(10);
}

void loop()
{
   
  delay(100); // this speeds up the simulation  

  //read potentiometer  
  int potVal = analogRead(12);
  //read joystick
  int joyVal = analogRead(27);
  //change person  
  if (joyVal > 2000 && count == 0) {
      name = people[index];
      //next name
      opencount = 0;
      index = (index + 1) % 6;
  }  
  else if(joyVal < 2000){
    count = 0;
  }
  //change weather
  if (potVal < 1000 and potVal > 100){
    //STEPPER MOTOR
    //Should only rotate if there is "sunny"  
    // Rotate a full turn
    while(true){ 
      moveSteps(true, 32 * 64, 3);
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setLedColorData(i, m_color[2][0], m_color[2][1], m_color[2][2]);
        strip.show();
        delay(delayval);
      }    
    }
    weatherIndex = 1;
    opencount = 0;
    //sun
  }
  if (potVal < 2000 and potVal > 1000){
    weatherIndex = 2;
    opencount = 0;
      //rain
    while(true){
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setLedColorData(i, m_color[0][0], m_color[0][1], m_color[0][2]);
        strip.show();
        delay(delayval);
      }
      delay(500);
    }
  }
  if (potVal < 3000 and potVal > 2000){
    weatherIndex = 3;
    opencount = 0;
    //snow
    while(true){
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setLedColorData(i, m_color[1][0], m_color[1][1], m_color[1][2]);
        strip.show();
        delay(delayval);
      }
      delay(500);
    }
    
  }
  if (potVal > 3000){
    weatherIndex = 4;
    opencount = 0;
    //cloudy
    while(true){
      Blink(10, 500);
    }
  }

  
  
  

  pirStat = digitalRead(pirPin); 
  if (pirStat == HIGH && opencount == 0) {            // if motion detected
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    Serial.println("Hey I got you!!!");
    if (weatherIndex == 1){
      string ans = sunny[name];
      if (ans == "yes"){
        openDoor();
        opencount +=1;
      }
    }
    else if (weatherIndex == 2){
      string ans = rain[name]; 
      if (ans == "yes"){
        openDoor();
        opencount +=1;
      }
    }
    else if (weatherIndex == 3){
      string ans = thunderstorm[name];  
      if (ans == "yes"){
        openDoor();
        opencount +=1;
      }
    }
    else if (weatherIndex == 4){
      string ans = cloudy[name];   
      if (ans == "yes"){
        openDoor();
        opencount +=1;
      }
    }
  } 
  // else {
  //   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
  // }



}

//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20));        // Control the speed
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

void openDoor(){
  //SERVO MOTOR
  for (posVal = 0; posVal <= 180; posVal += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOne.write(posVal);       // tell servo to go to position in variable 'pos'
      myservoTwo.write(posVal);       // tell servo to go to position in variable 'pos'
      delay(30);                   // waits 15ms for the servo to reach the position
    }
  for (posVal = 180; posVal >= 0; posVal -= 1) { // goes from 180 degrees to 0 degrees
    myservoOne.write(posVal);       // tell servo to go to position in variable 'pos'
    myservoTwo.write(posVal);       // tell servo to go to position in variable 'pos'
    delay(30);                   // waits 15ms for the servo to reach the position
  }  
}

void Blink(int blinknum, int blinkwait)
{
  for (int i = 0; i < blinknum; i++)
  {
    strip.setLedColorData(i, 35, 35, 35);
  }
  strip.show();
  delay(blinkwait);
  for (int j = 0; j < blinknum; j++)
  {
  strip.setLedColorData(j, 0, 0, 0);
  }
  strip.show();
  delay(blinkwait);
}

