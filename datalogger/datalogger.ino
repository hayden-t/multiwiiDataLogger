//
#include "protocol.h"

#ifndef serialstate_h
#define serialstate_h
#include "serialstate.h"
#endif

#define INBUF_SIZE 64

static uint8_t inBuf[INBUF_SIZE];
static uint8_t checksum;
static uint8_t commandMW;
static uint8_t offset;
static uint8_t dataSize;

static Protocol p;
int8_t c,n;


//see protocol.cpp for serial number definition

void setup()  
{

  DEBUG.begin(9600);
  MWSERIAL.begin(115200);
  
  
  DEBUG.println("Setup");

}

void loop() // run over and over
{

  uint8_t  datad = 0;
  uint8_t  *data = & datad;

  // If you dont need a certain log just comment out the two lines for sending and reading
  p.send_msp( MSP_ATTITUDE  ,data, 0);
  readData();
  p.send_msp( MSP_RAW_IMU  ,data, 0);
  readData();
  p.send_msp( MSP_RC  ,data, 0);
  readData();
  p.send_msp( MSP_RAW_GPS ,data, 0);
  readData(); 

}

void readData() {

  delay(60);

  while (MWSERIAL.available()) {

    byte c = MWSERIAL.read();

    if (c_state == IDLE) {
      c_state = (c=='$') ? HEADER_START : IDLE;
    } 
    else if (c_state == HEADER_START) {
      c_state = (c=='M') ? HEADER_M : IDLE;
    } 
    else if (c_state == HEADER_M) {
      c_state = (c=='>') ? HEADER_ARROW : IDLE;
    } 
    else if (c_state == HEADER_ARROW) {

      if (c > INBUF_SIZE) {  // now we are expecting the payload size
        c_state = IDLE;

      } 
      else {
        dataSize = c;
        offset = 0;
        checksum = 0;
        checksum ^= c;
        c_state = HEADER_SIZE;  
      }
    } 
    else if (c_state == HEADER_SIZE) {
      commandMW = c;
      checksum ^= c;
      c_state = HEADER_CMD;
    } 
    else if (c_state == HEADER_CMD && offset < dataSize) {
      checksum ^= c;
      inBuf[offset++] = c;
    } 
    else if (c_state == HEADER_CMD && offset >= dataSize) {

      if (checksum == c) {
        if (commandMW == MSP_ATTITUDE) {
          XYAngle result = p.evalAtt(inBuf);
          DEBUG.print("Attitude Recieved: ");//example output
          DEBUG.println(result.heading);
        }
        if (commandMW == MSP_RAW_IMU) {
          IMUValues result = p.evalIMU(inBuf);
          
        }
        if (commandMW == MSP_RC) {
          RCInput result = p.evalRC(inBuf);
         
        }
        if (commandMW == MSP_RAW_GPS) {
          GPSValues result = p.evalGPS(inBuf);
          
          
        }

      } 

      c_state = IDLE;
    }

  }
}



















