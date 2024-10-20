#include <SPI.h>
#include <mcp2515.h>
#define LED_BUILTIN 2

struct can_frame canMsg;
MCP2515 mcp2515(5);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);

    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
}
