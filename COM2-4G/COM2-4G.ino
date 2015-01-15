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
 *
 *
 */
 

#include <SPI.h>
#include "com_24g.h"



void setup(void)
{

  Serial.begin(57600);
  printf_begin();

  printf("\nPreparing NRF24L01 interface\n");
 
}
//
// Loop
//


void loop(void)
{
  
}
