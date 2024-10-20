#include <SPI.h>
#include <mcp2515.h>

#define LED_BUILTIN 2

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(5);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  canMsg1.can_id  = 0x0E1;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x8E;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  canMsg2.can_id  = 0x0E2;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x0E;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x08;
  canMsg2.data[4] = 0x01;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0xA0;
  
  // while (!Serial){
  //   Serial.println("Not INIT");
  // };
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  // delay(10000);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  if(mcp2515.sendMessage(&canMsg1)==MCP2515::ERROR_OK){

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  Serial.println("Messages sent1");

  };

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  if(mcp2515.sendMessage(&canMsg2)==MCP2515::ERROR_OK){

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("Messages sent2");

  };

  
  // delay(5000);
}
