/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * Mitsubishi HVAC protocol added by Vincent Cruvellier.
 *
 */

#include "IRremote2.h"

// TX PIN 9

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  //IR Demo send a cmd To Mitsubishi HVAC
 Serial.println("IR Demo send a cmd To Mitsubishi HVAC");
 Serial.println("Please any data to the Serial Interface in order to start the Demo");
 Serial.println("");
}

void loop() {
  
//  if (Serial.read() != -1) {
    
 // Serial.println("Switch OFF and Wait 15 Seconds to send ON command.");
      //irsend.sendHvacMitsubishi(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO_MOVE, true);
      //Sirsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO, NORMAL, true);
      //delay(15000);         
      //Serial.println("Turn ON\nCommand 'HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO_MOVE'  Next Command in 10 sec.");
      //irsend.sendHvacMitsubishi(HVAC_HOT, 23, FAN_SPEED_1, VANNE_AUTO_MOVE, false);
      irsend.sendHvacPanasonic(HVAC_HOT, 30, FAN_SPEED_AUTO, VANNE_AUTO, NORMAL, true);
      delay(10000);
/*      irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_H1, NORMAL, false);
      delay(10000);
      irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_H2, NORMAL, false);
      delay(10000);
      irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_H3, NORMAL, false);
      delay(10000);
      irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_H4, NORMAL, false);
      delay(10000);
      irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_H5, NORMAL, false);
      delay(20000);
  */ 
      /*
      Serial.println("Command 'HVAC_HOT, 23, FAN_SPEED_1, VANNE_AUTO_MOVE' sent.\n Waiting 60 Seconds to switch to FAN_SPEED_4.");
      delay(60000);
      irsend.sendHvacMitsubishi(HVAC_HOT, 25, FAN_SPEED_4, VANNE_H1, false);
      Serial.println("Command 'HVAC_HOT, 25, FAN_SPEED_4, VANNE_H1' sent. \n Waiting 30 Seconds to Send FAN_SPEED_SILENT, VANNE_H1.");
      delay(30000);
      irsend.sendHvacMitsubishi(HVAC_HOT, 22, FAN_SPEED_SILENT, VANNE_AUTO_MOVE, false);
      Serial.println("Command 'HVAC_HOT, 22, FAN_SPEED_SILENT, VANNE_AUTO_MOVE' sent.\n Waiting 30 Seconds to send OFF.");
      delay(30000);*/
      //irsend.sendHvacMitsubishi(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO_MOVE, true);
      
      //irsend.sendHvacPanasonic(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO, NORMAL, true);

      //Serial.println("Command sent. End Of Sketch");
      //delay(15000); // Let HVAC sleeping

  //}
}
