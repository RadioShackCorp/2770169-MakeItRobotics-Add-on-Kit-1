//********************************************************************************
// * File Name          : Bulldozer_home_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/20
// * Description        : Use your home IR remote control (for example, a TV remote) to cycle through the
// *                      RadioShack Make: it bulldozer robot functions.
// ********************************************************************************
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, see http://www.gnu.org/licenses/
//
/*****************************************************************************
  Point one of your home IR remote controls (for example, TV, DVD player)
  and press any button to cycle through the following commands. If you 
  press and hold the button, the robot will continuously repeat the cycle.
  
  STOP       <-------------------------|
  1st time  -> forward                 |
  2nd time  -> backward                | 
  3rd time  -> turn left               |
  4th time  -> turn right              |
  5th time  -> bulldozer blade up      |
  6th time  -> bulldozer blade down ---|   
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics bulldozer;   //declare object
// ***************************************************************************
// * Pin definition
// ***************************************************************************
#define PIN_IR      10   //define IR input
// ***************************************************************************
// *                            Power Up Init.
// ***************************************************************************
void setup() 
{
  pinMode(PIN_IR, INPUT);      //set IO INPUT
  digitalWrite(PIN_IR,HIGH);   //set PULL HIGH
  Serial.begin(10420);         //tell the Arduino to communicate with Make: it PCB
  delay(500);                  //delay 500ms
  bulldozer.all_stop();        //stop all motors
}
// ***************************************************************************
// *                            Main Loop 
// ***************************************************************************
void loop() 
{  
  static int motoract = 0;      //action number
  static int count = 0;         //filter counter
  //----------------------------------------------------------------- 
  //GET IR & ACTION PROGRAM
  while(digitalRead(PIN_IR));    //during a low signal, wait for the IR remote recever signal
  while(digitalRead(PIN_IR)==0); //wait for the signal to return to HIGH
  count++;                       //count +1 when count i greater than 10, then go action (this makes a software filter)
  if(count>10)
  {
    count=0;                     //begin the count
    motoract++;                  //next action
    if(motoract==7)              //total 7 action (0 to 6)
      motoract=0;                
    if(motoract==0)              //action 0
      bulldozer.all_stop();      //all motors stop
    else if(motoract==1)         //action 1 
      bulldozer.go_forward(60);  //go forward      
    else if(motoract==2)         //action 2 
      bulldozer.go_backward(60); //go backward
    else if(motoract==3)         //action 3 
      bulldozer.turn_front_left(60);   //turn left      
    else if(motoract==4)         //action 4
      bulldozer.turn_front_right(60);  //turn right        
    else if(motoract==5)         //action 5
    {
      bulldozer.all_stop();      //all motors stop  
      bulldozer.bulldozer_head_up(60); //bulldozer blade up
    }  
    else if(motoract==6)          
      bulldozer.bulldozer_head_down(60); //bulldozer blade down
    delay(500);                 //delay 500ms (to next action at least 500ms)
  }
}
