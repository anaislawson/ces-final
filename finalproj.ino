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

using namespace std;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::copy;

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
                                

map<string, string> thunderstorm = {"Anais", "no",},
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
const String people[6] = {"Anais, Sahory, Andre, Mark, Gen, Kennedi"};

Servo myservoOne;  // create servo object to control a servo
Servo myservoTwo;  // create servo object to control a servo

int posVal = 0;    // variable to store the servo position
int servoPin = 15; // Servo motor pin
char name[] = people[0];
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
      
      //next name
      index = (index + 1) % 6;
  }  
  else{
      count = 0;
  }
  //change weather
  if (potVal < 1000 and potVal > 100){
      //sun
  }
  if (potVal < 2000 and potVal > 1000){
      //rain
  }
  if (potVal < 3000 and potVal > 2000){
      //thunderstorm
  }
  if (potVal > 3000){
      //cloudy
  }

  //STEPPER MOTOR
  //Should only rotate if there is "sunny"  
  // Rotate a full turn
  moveSteps(true, 32 * 64, 3);
  delay(1000);
  
  
  //only run if the person and lighting is correct  
  //SERVO MOTOR
  for (posVal = 0; posVal <= 180; posVal += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(posVal);       // tell servo to go to position in variable 'pos'
    delay(15);                   // waits 15ms for the servo to reach the position
  }
  for (posVal = 180; posVal >= 0; posVal -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(posVal);       // tell servo to go to position in variable 'pos'
    delay(15);                   // waits 15ms for the servo to reach the position
  }  





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



