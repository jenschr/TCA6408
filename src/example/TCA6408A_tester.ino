#include "TCA6408.h"

TCA6408 ioExpander;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("init");
  // wake up I/O expansion
  ioExpander.begin();
  Serial.println("begin");
}

void loop() {
  uint8_t input;
  input = ioExpander.readInput(1);
  Serial.print(input, BIN);
  Serial.print(" 1 ");
  Serial.println( bitRead(input, 1) );
  
  delay(10);
}
