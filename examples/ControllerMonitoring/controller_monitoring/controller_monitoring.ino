#include <GamerBoy2x16.h>

#define DELAY 200

GamerBoy2x16 gb = GamerBoy2x16();

void setup() {
  gb.initialize();
  Serial.begin(9600);
}

void loop() {
  gb.update();

  Serial.println("A \t B \t X \t Y");
  Serial.println(String(gb.controller.a) + '\t' +
    String(gb.controller.b) + '\t' +
    String(gb.controller.x) + '\t' +
    String(gb.controller.y) + '\t'
  );
  
  delay(DELAY);
}
