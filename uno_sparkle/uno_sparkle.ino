void setup() {
  // 初始化数字引脚 13 为输出模式
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);   // 打开 LED
  delay(1000);              // 延时 1 秒
  digitalWrite(13, LOW);    // 关闭 LED
  delay(1000);              // 延时 1 秒
}
