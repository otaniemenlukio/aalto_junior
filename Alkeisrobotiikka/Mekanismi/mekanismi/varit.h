// Värit määriteltynä r,g,b muodossa
#define RED 255,0,0
#define GREEN 0,255,0
#define BLUE 0,0,255
#define WHITE 255,255,255
#define PINK 255,192,203
#define ORANGE 255,165,0
#define CYAN 0,255,255
#define YELLOW 255,255,0
#define PURPLE 128,0,128
#define MAGENTA 255,0,255



// Lista joka kuvaa sitä mikä nappi kauko-ohjaimessa tarkoittaa mitä väriä,
// esim. kauko-ohjaimen nappi 0 muuttaa värin punaiseksi koska varit[0] = punainen
uint32_t varit[] = {
  ledinauha.Color(RED),
  ledinauha.Color(GREEN), ledinauha.Color(BLUE), ledinauha.Color(WHITE),
  ledinauha.Color(PINK), ledinauha.Color(ORANGE), ledinauha.Color(CYAN),
  ledinauha.Color(YELLOW), ledinauha.Color(PURPLE), ledinauha.Color(MAGENTA)
};

void asetaNauhanVari(Adafruit_NeoPixel *s, uint32_t color) { // Vaihtaa nauhan värin annetuksi väriksi
  s->clear(); // Poistaa nauhasta edellisen värin

  int pixels = s->numPixels(); // tallentaa valojen määrän
  for (int i = 0; i < pixels; i++) { // jokaista valoa kohden
    s->setPixelColor(i, color); //  muutetaan valon väri määritetyksi väriksi
  }
  s->show(); // Näyttää muutoksen
}
