#include <GamerBoy2x16.h>

LimitedStack<byte> s = LimitedStack<byte>(3);

void setup() {
  Serial.begin(9600);
  Serial.println("Simple stack example");

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);

  Serial.print("Stack size: ");
  Serial.println(s.getSize());

  Serial.print("Top: ");
  Serial.println(s.top());

  Serial.print("Is full? ");
  Serial.println(s.isFull());

  while (!s.isEmpty()) {
    byte item = s.pop();
    Serial.println(item);
  }
}

void loop() {
}
