/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.11 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT


// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 27 bytes
  { 255,1,0,0,0,20,0,17,0,0,0,31,1,106,200,1,1,1,0,4,
  42,48,19,94,0,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct { 

    /* input variable */
  unsigned char slider_1; /* =0..100 slider position */

    /* other variable */
  unsigned char connect_flag;  /* =1 if wire connected, else =0 */

} RemoteXY; 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#include <Servo.h>  

Servo myservo; 
int ms = RemoteXY.slider_1*20+500;

void setup()  
{ 
  RemoteXY_Init ();  
     
  // TODO you setup code 
  myservo.attach(9); 
  RemoteXY.slider_1 = 50; 
   
} 

void loop()  
{  
  RemoteXY_Handler (); 

  // TODO you loop code 
  // use the RemoteXY structure for data transfer 

  int ms = RemoteXY.slider_1*20+500; 
  myservo.writeMicroseconds(ms); 

}
