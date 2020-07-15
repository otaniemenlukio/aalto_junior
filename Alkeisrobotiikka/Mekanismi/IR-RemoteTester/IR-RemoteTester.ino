#include <IRremote.h>

IRrecv irrecv(4);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Helou");
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)){
      Serial.println(results.value, HEX);
      irrecv.resume();
  }
}
