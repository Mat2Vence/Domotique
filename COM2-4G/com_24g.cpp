/*
 * com_24g.cpp
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
#include "RF24.h"
#include "printf.h"
#include "com_24g.h"



bool COM_24g::initiate()
{
    bool status = false;
	RF24 _radioCom(_ce,_csn);
	_radioCom.begin();
	// optionally, increase the delay between retries & # of retries
	_radioCom.setRetries(15,15);
	
	_radioCom.setChannel= _channel

	// optionally, reduce the payload size.  seems to improve reliability
	//_radioCom.setPayloadSize(8);

	// Open pipes to other nodes for communication
	_radioCom.openWritingPipe(_writingPipe);
	for (i=1;i<5;i++) {
		if (_readingPipe[i] != NULL) {
		_radioCom.openReadingPipe(i,pipes[i]);
		status = true;
		}
	}
	if (status == true) {
	_radioCom.startListening();
	} else {
	_radioCom.powerDown();
	}
return status;
}


 
bool COM_24g::sendFrame()
{
	// First, stop listening so we can talk
	_radioCom.stopListening(); 
 
	//Opening the writting Pipe
	_radioCom.openWritingPipe(_writingPipe);
	
	//put in place the Paypload
	_payload = 

	bool status = radio.write(&_payload, sizeof(_payload));

	//back in read mode
	_radioCom.startListening(); 
	
 
}

  
uint8_t COM_24g::isAvailable()
{
	if (_radioCom.available()) {
		for (i=1;i<5;i++) {
			if (_radioCom.available(i)) {
			uint8_t pipeAvailable = i;
			break;
			}
		}
	return pipeAvailable;	
	} else {
	return NULL;
	}


}


void COM_24g::listeningPipe();	//Listen all available pipes
{
  _radioCom.openReadingPipe(pipe, _readingPipe[pipe]);
  _radioCom.startListening();
  _radioCom.powerUp();
  printf("//NRF24 Module Sensor Enabled.\n");

}

void COM_24g::receiveFrame(uint8_t pipe);	// Decode the available frame on the pipe
{

Payload payload = (Payload) {
  CMD_WHO
};

len 	= _radioCom.getDynamicPayloadSize();  	// Size of the payload to read
done 	= _radioCom.read(payload, len);			// Read the payload
//printf("%u:%u:%u\n", done, pipeNo, len);

  switch (payload.type) {
      case CMD_WHO:
        printf("CMD_WHO:");
		_radioCom.COM_24g_data.partnum	= payload.data.partnum;			// part number
		_radioCom.COM_24g_data.parttype	= payload.data.parttype;		// type of part
		_radioCom.COM_24g_data.revision	= payload.data.revision;		// Revision number
		_radioCom.COM_24g_data.status	= payload.data.status;
		
		uint16_t   partnum		= payload.data.partnum;				// part number
		uint16_t   parttype		= payload.data.parttype;			// type of part
		uint16_t   revision		= payload.data.revision;			// Revision number
		uint8_t    status		= payload.data.status;
        printf("Part number %d of type %d - version of code is %d \n", partnum,parttype,revision);
        lastReceive = millis();
        break;
      default:
        printf("Unknown message.\n");
        break;
    }

}








}
