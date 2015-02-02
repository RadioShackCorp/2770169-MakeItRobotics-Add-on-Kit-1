//********************************************************************************
// * File Name          : Bulldozer_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/22
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the bulldozer robot.
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
  SW5 blade up
  SW6 blade down
*****************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics bulldozer; //declare object
// ***************************************************************************
// *                            Power Up Init.
// ***************************************************************************
void setup() 
{
  Serial.begin(10420);       //tell the Arduino to communicate with Make: it PCB
  bulldozer.remote_setup();  //remote control setup
  delay(500);                //delay 500ms
  bulldozer.all_stop();      //stop all motors
}
// ***************************************************************************
// *                            Main Loop 
// ***************************************************************************
void loop()
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=bulldozer.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;   //refresh the previous code 
    if(valueo==SW1)                    //SW1 action
    {
      bulldozer.bulldozer_head_up(0);  //stop bulldozer blade
      bulldozer.go_forward(60);        //go forward 
    }
    else if(valueo==SW3)               //SW3 action
    {
      bulldozer.bulldozer_head_up(0);  //stop bulldozer blade    
      bulldozer.go_backward(60);       //go backward
    }    
    else if(valueo==SW2)               //SW2 action
    {
      bulldozer.bulldozer_head_up(0);  //stop bulldozer head    
      bulldozer.turn_front_left(60);   //turn left      
    }
    else if(valueo==SW4)               //SW4 action
    {    
      bulldozer.bulldozer_head_up(0);  //stop bulldozer head     
      bulldozer.turn_front_right(60);  //turn right        
    }
    else if(valueo==SW5)               //SW5 action 
    {
      bulldozer.move_stop();           //stop wheels
      bulldozer.bulldozer_head_up(60); //move bulldozer blade up
    }  
    else if(valueo==SW6)               //SW6 action
    {
      bulldozer.move_stop();           //stop wheels
      bulldozer.bulldozer_head_down(60);  //move bulldozer blade down
    }      
    else                              //if no buttons are pushed
      bulldozer.all_stop();           //stop all motors
  }
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)              //interrupt code
{
  bulldozer.remote_scan();    //analyze signal from RadioShack Make: it Robotics Remote Control
}
