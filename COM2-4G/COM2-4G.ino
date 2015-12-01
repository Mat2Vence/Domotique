//#include <Printf.h>

/*
 * com_24g.h
 * Version 0.1 January, 2015
 * Copyright 2015 Mathieu THOMAS
 * For details, see http://www.emtee.fr
 *
 *
 * 
 * Communication through RF 2.4GHz using Payload
 * 
 * 
 *
 *
 */
 
#include <stdio.h>
#include <SPI.h>
#include "com_24g.h"
#include "RF24.h"
#include "printf.h"

//Instantiation of the COM object.
// conf for the mega 
uint8_t csn= 48;
uint8_t ce= 49;

uint8_t pipeNo;

//Configuration for the Nano
//uint8_t csn= 10;
//uint8_t ce= 9;

RF24 _myRF24(ce,csn);
COM_24g myCom(_myRF24);


void setup(void)
{

 Serial.begin(9600);
printf_begin();
  Serial.println("Preparing NRF24L01 interface");
    printf("\n check if the printf function is working\n");

myCom._miso	=50;		// uno d12 (pin 18) or mega d50 or nano 12
myCom._mosi	=51;		// uno d11 (pin 17) or mega d51 or nano 11
myCom._sck	=52;		// uno d13 (pin 19) or mega d52 or nano 13
myCom._csn	=48;		// uno d10 (pin 16) or mega d48 or nano 10
myCom._ce	=49;		// uno d9  (pin 15) or mega d49 or nano 9

//Setting of the myCom object
  myCom._readingPipe[1] = 0xFF00000002LL;
 
  myCom._writingPipe    = 0xFF00000001LL; 
  //myCom._writingPipe    = 0x0000000001LL; 
 
  myCom._channel        =3;
  myCom._maxRetry       =5; //number of retry in case of a failure in transmission --> max is 15

 myCom.initiate(_myRF24);
   Serial.println("Start COM");
    myCom.statusReportOnPC(_myRF24);


// Init of the Sat
// STEP 1 : WHOAMI    
    myCom._dataType    = WHOAMI;
    myCom._dataVersion  = 1;
    myCom._data.WHOAMI.partnum=0x001A;
    myCom._data.WHOAMI.parttype=0x0A0B;
    myCom._data.WHOAMI.revision=0x0001;
    
    Serial.println("Send WHOAMI");
    myCom.sendFrame(_myRF24);
    Serial.println("Done");

// STEP 2 : Listen for the Base answer
    Serial.println("Wait for the answer");
    myCom.listeningPipe(_myRF24);
    while (_myRF24.available(&pipeNo)) {
         Serial.println("There is a frame available");
         bool done = false;
         int len;
         while (!done) {
               done=myCom.receiveFrame(_myRF24);
               Serial.println("data read");
               Serial.println(myCom._data.YOUARE.partid);    
               //Serial.println(myCom._data.YOUARE.baseCmdAdd);    
               //Serial.println(myCom._data.YOUARE.base_encode);    

         }
    }

// STEP 3 : Write required Info in EEEPROM and Send READY


}


void loop(void)
{

// STEP 1 : WAKE-UP


// STEP 2 : Ask if there is something to do with CMD_ASK


// STEP 3 : Wait for Answer


    // STEP 3A : nothing to do --> go to sleep


    // STEP 3B : send something to HVAC
        // step 3B1 : send IR code

        //step 3B2 : send back the command received

        //step 3B3 : wait for sleep command from base
        
    
 
  //myCom.receiveFrame(_myRF24);

 

    delay(2500);

     
 /*

     myCom.listeningPipe(_myRF24);
  while (_myRF24.available(&pipeNo)) {
         Serial.println("There is a frame available");

    bool done = false;
    int len;
    while (!done) {
               done=myCom.receiveFrame(_myRF24);
                Serial.println("data read");
 Serial.println(myCom._data.CMD_WHO.partnum);
    }

      


      }*/
}
