#define TempPin A0 // Määrittelee vakion nimellä TempPin arvolla A0. Muuta arvoa jos vaihdat pinniä mihin sensori kytketään.

void setup() {
  Serial.begin(9600); // Tarvitaan, että serial consoleen voidaan tulostaa.
}

void loop() {
  int sensorinArvo = analogRead(TempPin); // Luetaan lämpötilamittarin antama arvo.
  float jannite = sensorinArvo * 5; // Muunnetaan se mittarin antamaksi jännitteeksi
  jannite = jannite / 1024.0; // Koska sensorin arvo on väliltä 0 - 1024

  float lampotila = (jannite - 0.5) * 100; // Lasketaan lämpötila hyödyntäen tietoa siitä miten sensori mittaa lämpöä 10 mV per aste, 500mV:n poikkeamalla

  
  Serial.println(lampotila); // Tulostetaan lämpötila Serial consoleen
  delay(1000); // Odotetaan 1000 millisekuntia eli 1 sekunti
}
