void setup() {
  // 初始化 GPIO 2 为输出模式
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);   // 打开 LED
  delay(1000);             // 延时 1 秒
  digitalWrite(2, LOW);    // 关闭 LED
  delay(1000);             // 延时 1 秒
}
