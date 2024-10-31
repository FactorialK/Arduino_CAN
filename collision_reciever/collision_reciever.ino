#include <SPI.h>
#include <mcp2515.h>
#include <DHT11.h>
#define LED_BUILTIN 2

const int DHT11_PIN = 15;   // ESP32 GPIO_15
const int MCP2515_PIN = 5;  // ESP32 GPIO_5

struct can_frame canMsg;
struct can_frame replyMsg;
MCP2515 mcp2515(MCP2515_PIN);
DHT11 dht11(DHT11_PIN);

int temperature = 0;
int humidity = 0;
int result = 0;

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);  // note: the board might have issues. Set 500KBPS, if you would like CAN 1000KBPS
  if (mcp2515.setFilterMask(MCP2515::MASK0, false, 0x7FF) == MCP2515::ERROR_OK) {
    Serial.println("Mask init ");
  };
  mcp2515.setFilterMask(MCP2515::MASK1, false, 0x7FF);

  mcp2515.setFilter(MCP2515::RXF0, false, 0x01);
  // mcp2515.setFilter(MCP2515::RXF1, false, 0x0e2);
  // mcp2515.setFilter(MCP2515::RXF2, false, 0x0e1);
  // // mcp2515.setFilter(MCP2515::RXF3, false, 0x0e2);
  // mcp2515.setFilter(MCP2515::RXF4, false, 0x0e1);
  // mcp2515.setFilter(MCP2515::RXF5, false, 0x0e2);
  mcp2515.setListenOnlyMode();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    if (canMsg.data[0] == 0xAA && canMsg.data[1] == 0xBB && canMsg.data[2] == 0xCC) {
      result = dht11.readTemperatureHumidity(temperature, humidity);
      if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
      } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
      }
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    }



  }
}
