/*!
 * @file  send.ino
 * @brief  CAN-BUS Shield, send data
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Arduinolibrary
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#include "DFRobot_MCP2515.h"


const int SPI_CS_PIN = 10;
unsigned char data[3];
uint32_t RecieveId;
unsigned char len;
unsigned char buf[8];


DFRobot_MCP2515 CAN(SPI_CS_PIN);  // Set CS pin

void setup() {
  Serial.begin(115200);
  data[0] = 0xAA;
  data[1] = 0xBB;
  data[2] = 0xCC;

  while (CAN.begin(CAN_500KBPS)) {  // init can bus : baudrate = 500k
    Serial.println("DFROBOT's CAN BUS Shield init fail");
    Serial.println("Please Init CAN BUS Shield again");
    delay(1000);
  }
  Serial.println("DFROBOT's CAN BUS Shield init ok!\n");
}

bool isReady = false;

void loop() {
  while (!isReady) {
    // CAN.readMsgBufID(RecieveId, len, buf);
    CAN.readMsgBuf(&len, buf);
    RecieveId = CAN.getCanId();
    Serial.println(RecieveId);
    if (RecieveId == 0x122) {
      isReady = true;
    }
  }
  // // send data:  id = 0x01, standrad flame, data len = 8, data: data buf

  if (CAN.sendMsgBuf(0x01, 0, 3, data) == MCP2515_OK) {
    Serial.println("Benign Messages sent");
  }
  CAN.readMsgBuf(&len, buf);
  RecieveId = CAN.getCanId();
  if (RecieveId == 0x100) {
    isReady = false;
  }
}
