#include <Servo.h> // Servo-kirjasto, tarvitaan servojen käyttämiseen

// Etäisyyssensorin pinnit
#define TRIG_PIN 9 // Tarkoittaa arduinon digitaalista pinniä 9
#define ECHO_PIN 10

// Servon pinnit
#define SERVO_PIN 2

// Etäisyys jolla laatikko avautuu senttimetreinä
#define AVAUSETAISYYS 30

Servo servo;

void setup() {
  // Valmistelee etäisyyssensorin pinnit lähettämistä ja vastaanottamista varten
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Yhdistää koodin Servo-objektin ja servon pinnissä SERVO_PIN
  servo.attach(SERVO_PIN);
}


// Metodi joka mittaa etäisyyden sensorin avulla
double mittaaEtaisyys() {
  // Käytännössä lähettää sensorille käskyn mitata.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH); // Odottaa että sensori lähettää signaalin, palauttaa ajan joka on odotettu
   /* 
    Koska sensori toimii lähettämällä äänen ja odottamalla että se palaa takaisin, etäisyys saadaan  
    Kertomalla kulunut aika äänen nopeudella muunnettuna mikrosekunneiksi senttimetrissä.
    se jaetaan kahdella koska kulunut aika on äänen lähdöstä.
   */
  double distance = duration * 0.034 / 2; 

  return distance; // Palautetaan kulunut etäisyys
}

void avaaLaatikko() { // Avaa laatikon eli kääntää servon 90 asteen kulmaan 
    servo.write(90);
}

void suljeLaatikko() { // Sulkee laatikon eli kääntää servon 0 asteen kulmaan
    servo.write(0);
}

void loop() {
  double etaisyys = mittaaEtaisyys(); // Mittaa etäisyys sensorista ja tallenna se muuttujaan etaisyys
  
  if(etaisyys < AVAUSETAISYYS) { // Jos etaisyys on pienempi kuin avausetäisyys, avaa laatikko
    avaaLaatikko();
  } else { // muuten sulje laatikko
    suljeLaatikko();
  }

  delay(2000); // Odota 2 sekuntia
}
