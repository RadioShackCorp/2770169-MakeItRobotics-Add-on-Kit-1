//********************************************************************************
// * File Name          : Drill_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/23
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the drilling robot.
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
/****************************************************************************
  Press the following buttons (SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 rotate drill clockwise
  SW6 rotate drill counterclockwise
*****************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics drilling; //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
void setup() 
{ 
  Serial.begin(10420);         //tell the Arduino to communicate with Make: it PCB
  drilling.remote_setup();     //remote control setup
  delay(500);                  //delay 500ms
  drilling.all_stop();         //stop all motors
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=drilling.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;    //refresh the previous code      
    if(valueo==SW1)                              //SW1 action
    {
      drilling.drilling_head_clockwise(0);       //stop drill head
      drilling.go_forward(80);                   //go forward
    }
    else if(valueo==SW3)                         //SW3 action
    {
      drilling.drilling_head_clockwise(0);       //stop drill head  
      drilling.go_backward(80);                  //go backward
    }    
    else if(valueo==SW2)                         //SW2 action
    {
      drilling.drilling_head_clockwise(0);       //stop drill head
      drilling.turn_left(80);                    //turn left
    }
    else if(valueo==SW4)                         //SW4 action   
    {    
      drilling.drilling_head_clockwise(0);       //stop drill head
      drilling.turn_right(80);                   //turn right
    }
    else if(valueo==SW5)                         //SW5 action
    {
      drilling.move_stop();                      //stop wheels
      drilling.drilling_head_clockwise(80);      //rotate drill head clockwise
    }  
    else if(valueo==SW6)                         //SW5 action
    {
      drilling.move_stop();                      //stop wheels
      drilling.drilling_head_counterclockwise(80);  //rotate drill head counterclockwise 
    }      
    else                                         //if no buttons are pushed
      drilling.all_stop();                       //stop all motors
  }
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)           //interrupt code
{
  drilling.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
