// Tuodaan tarvittavat kirjastot
#include <Servo.h>
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

// Ledien määrä
#define LEDIEN_MAARA 7

// Ledien kirkkaus
#define BRIGHTNESS 100

// Eri komponenttien pinnit
#define NEOPIXEL_PIN 3
#define SERVO_PIN 6
#define IR_PIN 4

Servo s; // Servomuuttujan määrittely

IRrecv vastaanotin(IR_PIN); // Määritellään IR-vastaaotin ja kytketään se pinniin
decode_results results; // Luodaan jo nyt muuttuja johon tullaan tallennetamaan vastaaottimen saamat signaalit

Adafruit_NeoPixel ledinauha = Adafruit_NeoPixel(LEDIEN_MAARA, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); // Ledinauhan määrittely

// Tuodaan kaksi tiedostoa jotka sisältävät erilaisia määritelmiä
#include "varit.h" // Tiedostossa määritellään eri värien RGB arvoja, jos haluat muuttaa värejä tee se täältä
#include "kaukoohjain.h" // Kaukoohjaimen eri napit.


// Muuttujia ledinauhan logiikkaa varten
bool valotPaalla = false; // Onko ledit päällä
bool shouldUpdate = false; // Pitäisikö muuttaa jotain ledinauhasta
uint32_t color = ledinauha.Color(WHITE); // Ledinauhan väri
uint32_t newColor = ledinauha.Color(WHITE); // Ledinauhan mahdollinen uusi väri


void setup() {
  s.attach(SERVO_PIN);   // Yhdistetään servomuuttuja pinniin

  vastaanotin.enableIRIn(); // Käynnistetään IR-Vastaanotin
  vastaanotin.blink13(true); // Arduinossa välkkyy valo kun vastaanotin saa signaalia


  ledinauha.begin();  // Käynnistetään ledinauha
  ledinauha.clear();  // Valmistellaan kaikki ledinauhan valot tyhjiksi
  ledinauha.show(); // Varmistetaan että muutos tapahtuu myös oikeassa nauhassa

  ledinauha.setBrightness(BRIGHTNESS); // Asetetaan ledinauhan kirkkaus, tämä kuuluu tehdä vain kerran

}
void loop() {
  if (vastaanotin.decode(&results)) {
    long long value = results.value; // Muuttuja joka kuvaa saatua koodia
    vastaanotin.resume(); // Jatka signaalien kuuntelua

    switch (value) {
      case VOL_YLOS: // Jos voluuminappia ylös painetaan
        valotPaalla = true; // Muuta muuttujaa joka kuvaa sitä ovatko valot päällä
        shouldUpdate = true; // Pitää päivittää, koska valojen päälläolotila on muuttunut
        s.write(0); // Käännetään servoa joka nostaa mekanismia
        break;
      case VOL_ALAS:
        valotPaalla = false; // Muuta muuttujaa joka kuvaa sitä ovatko valot päällä
        shouldUpdate = true; // Pitää päivittää, koska valojen päälläolotila on muuttunut
        s.write(120); // Käännä servoa
        break;
      /*
         Seuraavat caset tarkastavat onko jotain kaukosäätimen numeronapeista painettu,
         jos on niin se muuttaa ledinauhan väriä
      */
      case NOLLA:
        newColor = varit[0]; // Värilista on määritelty varit.h tiedostossa
        break;
      case YKSI:
        newColor = varit[1];
        break;
      case KAKSI:
        newColor = varit[2];
        break;
      case KOLME:
        newColor = varit[3];
        break;
      case NELJA:
        newColor = varit[4];
        break;
      case VIISI:
        newColor = varit[5];
        break;
      case KUUSI:
        newColor = varit[6];
        break;
      case SEITSEMAN:
        newColor = varit[7];
        break;
      case KAHDEKSAN:
        newColor = varit[8];
        break;
      case YHDEKSAN:
        newColor = varit[9];
        break;
    }
  }

  if (newColor != color) { // Jos väri on muuttunut
    color = newColor; // Koska väriä muutetaan
    shouldUpdate = true; // Väri on muuttunut, eli valoja pitää päivittää
  }
  if (shouldUpdate) {
    if (valotPaalla) { // Jos valot on päällä
      asetaNauhanVari(&ledinauha, color); // Vaihtaa ledinauhan värin
    } else { // muuten
      // Vaihda värit pois
      ledinauha.clear();
      ledinauha.show();
    }
  }
  shouldUpdate = false; // Vaihdetaan shouldUpdate falseksi, koska emme tiedä muuttuuko jotain seuraavalla kerralla kun loop kutsutaan
}
