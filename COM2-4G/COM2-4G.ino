#include <Printf.h>

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
uint8_t csn= 48;
uint8_t ce= 49;
RF24 _myRF24(csn,ce);
COM_24g myCom(_myRF24);


void setup(void)
{

 Serial.begin(9600);
printf_begin();
  Serial.println("Preparing NRF24L01 interface");
    printf("\n check if the printf function is working\n");


//Setting of the myCom object
  myCom._readingPipe[1] = 0xF0F0F0F0E1LL;
  myCom._readingPipe[2] = 0xF0F0F0F0D2LL;
  myCom._readingPipe[3] = 0xE8E8F0F0E1LL;
  myCom._readingPipe[4] = 0xF0F0F0F0E2LL;
  myCom._writingPipe    = 0xFFF0F0F0E1LL; 
  myCom._channel        =1;
  myCom._maxRetry       =5; //number of retry in case of a failure in transmission --> max is 15

 myCom.initiate(_myRF24);
 
}


void loop(void)
{
  while(1) {
    Serial.println("We are in the loop");
    myCom.statusReportOnPC(_myRF24);

     delay(20000);
  }
}
