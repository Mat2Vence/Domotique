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


// **************************************************************
// Creation of a 2.4Ghz connection
// input :
// output :
//
RF24 newCom24g(CE_PIN, CSN_PIN) {

RF24 radio(CE_PIN, CSN_PIN);

return radio;
}

// **************************************************************
// Send a frame through 2.4GHz
// input :
// output :
//
bool doSendMsg(RF24 radio, [] pipe_table, pipe, payloadr)
{
  radio.stopListening();
  radio.openWritingPipe(pipe_table[pipe]);
  bool done = (radio.write(&payloadr, sizeof(payloadr)), true);
  if (done) {
    printf("OK %d ", payloadr.type);
  }
  else {
    printf("NOK ");
    //printf("Transmission -> (%d) OK\t",sizeof(payload));
  }
  printf("Tr %d bytes / max %u -> [%u/%u/%u]\n", sizeof(payloadr), radio.getPayloadSize(), done, true, radio.isAckPayloadAvailable());
  //delay(500);
  //radio.startListening();
}

// **************************************************************
// Start Listening the 2.4GHz
// input :
// output :
//
void doStartListening(RF24 radio) {
radio.startListening();
}


// **************************************************************
// Start Listening the 2.4GHz
// input :
// output :
//
void doOpenPipeForReading(RF24 radio, [] pipe_table, pipe_adress_id, pipe2use)
{
  radio.openReadingPipe(pipe2use, pipe_table[pipe_adress_id]);
  radio.startListening();
  radio.powerUp();
  printf("//NRF24 Module Sensor Enabled.\n");

}


// **************************************************************
// Start Listening the 2.4GHz
// input :
// output :
//
void doSetupCOM24g(RF24 radio, channel) {
  radio.begin();
  radio.setRetries( 15, 15);
  //radio.enableDynamicPayloads();
  radio.setChannel(channel);
  //radio.enableAckPayload();
  //radio.disableCRC();
  //radio.setAutoAck(true);
  
}


// **************************************************************
// Decoding a Payload
// input :
// output :
//
void doReceiveCOM24g(RF24 radio) {

Payload payload = (Payload) {
  SENSOR_STATION
};

    while (!done) {
      len = radio.getDynamicPayloadSize();  // Size of the payload to read
      done = radio.read(payload, len);	// Read the payload
      //printf("%u:%u:%u\n", done, pipeNo, len);
    }
   switch (payload.type) {
      case SENSOR_DHT:
        printf("SENSOR_DHT:");

        printf("packet %d:%d Temp:%f Humidity:%f Dewpoint:%f status:%u \n", len, sizeof(payload), payload.data.SENSOR_DHT.temperature, payload.data.SENSOR_DHT.humidity, payload.data.SENSOR_DHT.dewpoint, payload.data.SENSOR_DHT.status);
        lastReceive = millis();
        break;
      case SENSOR_DUST:
        printf("SENSOR_DUST:");
        printf("packet %d:%d LPO:%d RatioDust:%f ConcentrationDUST:%f status:%u \n", len, sizeof(payload), payload.data.SENSOR_DUST.LowPpulseOccupancyDUST,
               payload.data.SENSOR_DUST.RatioDUST, payload.data.SENSOR_DUST.ConcentrationDUST, payload.data.SENSOR_DUST.status);
        lastReceive = millis();
        break;
      case SENSOR_LIGHT:
        printf("SENSOR_LIGHT:");
        printf("packet %d:%d Light:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_LIGHT.AnalogValue, payload.data.SENSOR_LIGHT.status);
        lastReceive = millis();
        break;
      case SENSOR_UV:
        printf("SENSOR_UV:");
        printf("packet %d:%d UV:%d Index:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_UV.AnalogValue, payload.data.SENSOR_UV.IndexUV, payload.data.SENSOR_UV.status);
        lastReceive = millis();
        break;
      case SENSOR_SOUND:
        printf("SENSOR_SOUND:");
        printf("packet %d:%d Sound:%u Max: %u status:%u \n", len, sizeof(payload), payload.data.SENSOR_SOUND.AnalogValue, payload.data.SENSOR_SOUND.MaxValue, payload.data.SENSOR_SOUND.status);
        lastReceive = millis();
        break;
      default:
        printf("Unknown message.\n");
        break;
    }

}




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








//
// Hardware configuration
//
/*
radio 7 (miso) to uno d12 (pin 18) or mega d50
radio 6 (mosi) to uno d11 (pin 17) or mega d51
radio 5 (sck)  to uno d13 (pin 19) or mega d52
radio 4 (csn)  to uno d10 (pin 16) or mega d48
radio 3 (ce)   to uno d9  (pin 15) or mega d49
radio 2 (3.3v) to uno 3.3v
radio 1 (gnd)  to uno gnd
*/
// **********************************************************************
// * SPI
// **********************************************************************
// * NRF24L01+
// Module NRF24L01+ (version + => I/O 5V Tolerant)
// !!!WARNING!!! powered at 3.3V, a capacitor is mandatory to be added in order to have module working properly.
// WIKI: http://www.dx.com/fr/p/nrf24l01-rf-board-b-296420
// DATASHEET: http://www.wvshare.com/downloads/accBoard/NRF24L01-RF-Board-B.7z
#define NRF24L01_CE_PIN	 9  	// nRF24L01 SPI CE Pin 
#define NRF24L01_CSN_PIN  10 	// nRF24L01 SPI CSN Pin 

//*****************************
// * NRF24L01 CONFIGURATION
#define NRF24L01_USE_ACK true	// Set auto ACK configuration Options.
RF24 radio(NRF24L01_CE_PIN, NRF24L01_CSN_PIN); // Set up nRF24L01 radio on SPI bus plus pins CE, CSN
// NRF24 Radio pipe addresses for the 2 nodes to communicate, only one used actually
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xE8E8F0F0E1LL, 0xF0F0F0F0E2LL }; // 1: Station 2: ...
uint8_t pipeNo;
long starttime, lastReceive;
const int Relay = 3;
int reset_count=0;

Payload payload = (Payload) {
  SENSOR_STATION
};

Payload payloadr = (Payload) {
  SENSOR_STATION
};

bool doSendMsg()
{
  radio.stopListening();
  radio.openWritingPipe(pipes[0]);
  delay(20);
  bool done = (radio.write(&payloadr, sizeof(payloadr)), true);
  if (done) {
    printf("OK %d ", payloadr.type);
  }
  else {
    printf("NOK ");
    //printf("Transmission -> (%d) OK\t",sizeof(payload));
  }
  printf("Tr %d bytes / max %u -> [%u/%u/%u]\n", sizeof(payloadr), radio.getPayloadSize(), done, true, radio.isAckPayloadAvailable());
  //delay(500);
  radio.startListening();
}

void setup(void)
{

  Serial.begin(57600);
  printf_begin();

  printf("\nPreparing NRF24L01 interface\n");
  radio.begin();
  radio.setRetries( 15, 15);
  //radio.enableDynamicPayloads();
  radio.setChannel(120);
  //radio.enableAckPayload();
  //radio.disableCRC();
  //radio.setAutoAck(true);
  radio.openReadingPipe(2, pipes[1]);
  radio.openReadingPipe(3, pipes[2]);
  radio.openReadingPipe(1, pipes[0]);
  //	radio.openReadingPipe(1,pipes[0]);
  radio.printDetails();

  /*
    // NRF24 init
    radio.begin(); // Setup and configure 2.4ghz rf radio
    radio.stopListening();
    radio.setRetries(15,15);
    radio.setChannel(120);
    //radio.disableCRC(); //CRC enabled by default
    radio.enableAckPayload();
    radio.setAutoAck(NRF24L01_USE_ACK);
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]); // Not used reading actually
    radio.openReadingPipe(2,pipes[0]); // Not used reading actually
    radio.openReadingPipe(3,pipes[2]); // Not used reading actually
    radio.printDetails();
    //NRF24L01_databuf[0] = STATION_NODE; // Assign Station Node
    if (radio.testRPD()) {
      printf("Warning Channel is busy\n!!");
    }
    radio.powerUp();
    printf("//NRF24 Module Sensor Enabled.\n");*/
  radio.startListening();
  delay(200);
  radio.powerUp();
  printf("//NRF24 Module Sensor Enabled.\n");
  payloadr.Version = PAYLOAD_VERSION; // initialize data for all payload -- PAYLOAD_VERSION; from sensor_payload.h
  payloadr.Station_id = 55; // initialize data for all payload 
  payloadr.Node = 0; // Master primary
  payloadr.type =  SENSOR_STATION;
  payloadr.data.SENSOR_STATION.Station_id = 55;
  payloadr.data.SENSOR_STATION.Power_Voltage = 55 ;
  payloadr.data.SENSOR_STATION.status = 55;
  doSendMsg();  // send an hello world !
  starttime = millis();//get the current time;
  lastReceive = millis();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  delay(200);
}
//
// Loop
//


void loop(void)
{
  while (radio.available(&pipeNo)) {
    bool done = false;
    int len;
    while (!done) {
      len = radio.getDynamicPayloadSize();  // Size of th epayload to read
      done = radio.read(&payload, len);	// Read the payload
      //printf("%u:%u:%u\n", done, pipeNo, len);
    }
    ////
    switch (payload.type) {
      case SENSOR_DHT:
        printf("SENSOR_DHT:");
        //printf("packet %d:%d Temp:%d Humidity:%d Dewpoint:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_DHT.temperature, payload.data.SENSOR_DHT.humidity, payload.data.SENSOR_DHT.dewpoint, payload.data.SENSOR_DHT.status);
        //char buffer[255];
        printf("packet %d:%d Temp:%f Humidity:%f Dewpoint:%f status:%u \n", len, sizeof(payload), payload.data.SENSOR_DHT.temperature, payload.data.SENSOR_DHT.humidity, payload.data.SENSOR_DHT.dewpoint, payload.data.SENSOR_DHT.status);
        lastReceive = millis();
        break;
      case SENSOR_DUST:
        printf("SENSOR_DUST:");
        printf("packet %d:%d LPO:%d RatioDust:%f ConcentrationDUST:%f status:%u \n", len, sizeof(payload), payload.data.SENSOR_DUST.LowPpulseOccupancyDUST,
               payload.data.SENSOR_DUST.RatioDUST, payload.data.SENSOR_DUST.ConcentrationDUST, payload.data.SENSOR_DUST.status);
        lastReceive = millis();
        break;
      case SENSOR_MQ2:
        printf("SENSOR_MQ2:");
        printf("packet %d:%d LPG:%f CO:%f SMOKE:%f MQ2:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_MQ2.LPG_Concentration,
               payload.data.SENSOR_MQ2.CO_Concentration, payload.data.SENSOR_MQ2.SMOKE_Concentration, payload.data.SENSOR_MQ2.AnalogValue, payload.data.SENSOR_MQ2.status);
        lastReceive = millis();
        break;
      case SENSOR_AQS:
        printf("SENSOR_AQS:");
        printf("packet %d:%d AQS:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_AQS.AnalogValue, payload.data.SENSOR_AQS.status);
        lastReceive = millis();
        break;
      case SENSOR_LIGHT:
        printf("SENSOR_LIGHT:");
        printf("packet %d:%d Light:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_LIGHT.AnalogValue, payload.data.SENSOR_LIGHT.status);
        lastReceive = millis();
        break;
      case SENSOR_MQ131:
        printf("SENSOR_MQ131:");
        printf("packet %d:%d Ozone:%f Chlorine:%f MQ131:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_MQ131.OzonePPM, payload.data.SENSOR_MQ131.ChlorinePPM,
               payload.data.SENSOR_MQ131.AnalogValue, payload.data.SENSOR_MQ131.status);
        break;
      case SENSOR_UV:
        printf("SENSOR_UV:");
        printf("packet %d:%d UV:%d Index:%d status:%u \n", len, sizeof(payload), payload.data.SENSOR_UV.AnalogValue, payload.data.SENSOR_UV.IndexUV, payload.data.SENSOR_UV.status);
        lastReceive = millis();
        break;
      case SENSOR_SOUND:
        printf("SENSOR_SOUND:");
        printf("packet %d:%d Sound:%u Max: %u status:%u \n", len, sizeof(payload), payload.data.SENSOR_SOUND.AnalogValue, payload.data.SENSOR_SOUND.MaxValue, payload.data.SENSOR_SOUND.status);
        lastReceive = millis();
        break;
      case SENSOR_STATION:
        printf("SENSOR_STATION:");
        printf("packet %d:%d ID:%u PowerVoltage:%u status:%u \n", len, sizeof(payload), payload.data.SENSOR_STATION.Station_id, payload.data.SENSOR_STATION.Power_Voltage, payload.data.SENSOR_STATION.status);
        break;
      case SENSOR_BMP085:
        printf("SENSOR_BMP085:");
        printf("packet %d:%d Temp:%f Pressure:%d Altitude:%f status:%u \n", len, sizeof(payload), payload.data.SENSOR_BMP085.temperature, payload.data.SENSOR_BMP085.Pressure, payload.data.SENSOR_BMP085.Altitude, payload.data.SENSOR_BMP085.status);
        lastReceive = millis();
        break;
      case WS2355_TEMP:
        printf("WS2355_TEMP:");
        printf("packet %d:%d Temp:%f status:%u \n", len, sizeof(payload), payload.data.WS2355_TEMP.temperature, payload.data.WS2355_TEMP.status);
        break;
      case WS2355_HUM:
        printf("WS2355_HUM:");
        printf("packet %d:%d Humidity:%f status:%u \n", len, sizeof(payload), payload.data.WS2355_HUM.humidity, payload.data.WS2355_HUM.status);
        break;
      case WS2355_RAIN:
        printf("WS2355_RAIN:");
        printf("packet %d:%d Total Rain:%f status:%u \n", len, sizeof(payload), payload.data.WS2355_RAIN.totalrain, payload.data.WS2355_RAIN.status);
        break;
      case WS2355_WIND:
        printf("WS2355_WIND:");
        printf("packet %d:%d Speed:%f Direction:%s status:%u \n", len, sizeof(payload), payload.data.WS2355_WIND.speed,
               strWindDirection[payload.data.WS2355_WIND.direction], payload.data.WS2355_WIND.status);
        break;
      default:
        printf("Unknown message.\n");
        break;
    }
    radio.startListening();
  }
  if ((millis() - starttime) >= 10000) { // Toutes les 3 minutes
    starttime = millis();//get the current time;
    uint16_t lastDeltaReceive = (uint16_t) (millis() - lastReceive) / 10000;
    printf("Last receive (seconds) = %u.\n", lastDeltaReceive);
    payloadr.data.SENSOR_STATION.Power_Voltage = lastDeltaReceive ;
    if (lastDeltaReceive > 90) { // 15 Minutes
         payloadr.data.SENSOR_STATION.status = reset_count++;
         if (reset_count > 1023) { reset_count =1; }
         doSendMsg();
         digitalWrite(Relay, HIGH);
         doSendMsg();
         delay(500); // Let time for the reset.
         doSendMsg();
         digitalWrite(Relay, LOW);
         doSendMsg();         
         lastReceive = millis(); //reinitialize
    }
    delay(20);
    printf(">");
    doSendMsg();
    radio.startListening();
  }
  delay(50);
}
