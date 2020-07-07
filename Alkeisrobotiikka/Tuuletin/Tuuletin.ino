// Kirjasto servojen käyttämiseen
#include <Servo.h>

// Määrittelee eri komponenttien pinnit
#define SAATOVASTUS_PINNI A0
#define MOOTTORIN_PINNI 3
#define SERVO_PINNI 2

// Montako astetta servo kääntyy
#define KAANTYMIS_LIMIT 120

// Servomuuttuja
Servo s; 

void setup() {
 s.attach(SERVO_PINNI); // Yhdistää servomuuttujan ja pinnissä 
}

void vaihdaMoottorinNopeutta() {
   int saatovastusArvo = analogRead(SAATOVASTUS_PINNI);  // Lukee säätövastuksen arvon
   int moottorinNopeus = map(saatovastusArvo, 0, 1023, 0, 255); // Muuntaa sen moottorin tukemaan arvoon
   analogWrite(MOOTTORIN_PINNI, moottorinNopeus);  // Kertoo moottorille nopeuden jolla pyöriä

}

void loop() {
  // Kääntää servon 0:sta-120:een asteeseen ja takaisin, lisäksi päivittää moottorin nopeutta joka käännöksellä.
  for (int asteet = 0; asteet <= KAANTYMIS_LIMIT; asteet++) { 
    s.write(asteet);  // Kertoo servolle että pitää kääntyä tiettyihin asteisiin
    vaihdaMoottorinNopeutta(); // Päivittää moottorin nopeuden säätövastuksen arvon mukaan
    delay(15); // Odottaa että servo on siirtynyt edelliseen pisteeseen
  }
  // Toistaa edellisen mutta taaksepäin
  for (int asteet = KAANTYMIS_LIMIT; asteet >= 0; asteet--) {
    s.write(asteet);
    vaihdaMoottorinNopeutta();           
    delay(15);                       
  }
}
