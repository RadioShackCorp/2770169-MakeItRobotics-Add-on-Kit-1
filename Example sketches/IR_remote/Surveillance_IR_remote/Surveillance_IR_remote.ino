//********************************************************************************
// * File Name          : Surveillance_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/23
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the surveillance robot.
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
  SW5 rotate platform clockwise
  SW6 rotate platform counterclockwise
*****************************************************************************/
#include <MakeItRobotics.h> //install library
MakeItRobotics surveillance; //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
void setup() 
{
  Serial.begin(10420);            //tell the Arduino to communicate with Make: it PCB
  surveillance.remote_setup();    //remote control setup
  delay(500);                     //delay 500ms
  surveillance.all_stop();        //stop all motors
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=surveillance.remote_value_read();  //to read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;    //refresh the previous code    
    if(valueo==SW1)                                 //SW1 action
    {
      surveillance.surveillance_head_clockwise(0);  //stop platform 
      surveillance.go_forward(80);                  //go forward    
    }
    else if(valueo==SW3)                            //SW3 action
    {
      surveillance.surveillance_head_clockwise(0);  //stop platform       
      surveillance.go_backward(80);                 //go backward 
    }    
    else if(valueo==SW2)                            //SW2 action
    {
      surveillance.surveillance_head_clockwise(0);  //stop platform      
      surveillance.turn_left(80);                   //turn left          
    }
    else if(valueo==SW4)                            //SW4 action
    {    
      surveillance.surveillance_head_clockwise(0);  //stop platform     
      surveillance.turn_right(80);                  //turn right          
    }
    else if(valueo==SW5)                            //SW5 action    
    {
      surveillance.move_stop();                     //stop wheels        
      surveillance.surveillance_head_clockwise(45); //rotate platform clockwise
      delay(75);                                    //delay 75ms
      surveillance.surveillance_head_clockwise(0);  //stop platform 
      delay(75);                                    //delay 75ms 
      valueo=0;                                     //clear the value; the program will go into this case again
    }  
    else if(valueo==SW6)                            //SW6 action   
    {
      surveillance.move_stop();                     //stop wheels            
      surveillance.surveillance_head_counterclockwise(45);  //rotate platform counterclockwise
      delay(75);                                    //delay 75ms
      surveillance.surveillance_head_clockwise(0);  //stop platform     
      delay(75);                                    //delay 75ms
      valueo=0;                                     //clear the value; the program will go into this case again   
    }      
    else                                            //if no buttons are pushed
      surveillance.all_stop();                      //stop all motors
  }
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  surveillance.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
