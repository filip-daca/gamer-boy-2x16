#include <GamerBoy2x16.h>

#define DELAY 200

GamerBoy2x16 gb = GamerBoy2x16();

void setup() {
  gb.initialize();
  Serial.begin(9600);
}

void loop() {
  gb.update();

  Serial.println("A \t B \t X \t Y \t L \t R \t U \t D");
  Serial.println(String(gb.controller.a) + '\t' +
    String(gb.controller.b) + '\t' +
    String(gb.controller.x) + '\t' +
    String(gb.controller.y) + '\t' +
    String(gb.controller.left) + '\t' +
    String(gb.controller.right) + '\t' +
    String(gb.controller.up) + '\t' +
    String(gb.controller.down) + '\t'
  );
  
  delay(DELAY);
}
