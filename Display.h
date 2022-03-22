#pragma once

#include <Adafruit_NeoPixel.h>

#define LED_PIN 18 //Pin des LED-Bands
#define NUMPIXELS 114 //Anzahl der LEDs
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_RGBW + NEO_KHZ800); //Inizialisierung der NeoPixels Bibliothek

// TODO:
// Remove inputMessage1, brightness as global and night-mode time management

const uint8_t heart[] = { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 };
const uint8_t kati[] = { 0, 1, 2, 3 };
const uint8_t andi[] = { 37, 38, 39, 40 };
const uint8_t wilma[] = { 26, 27, 28, 37, 38 };

void leuchten(int n) {
  if (shutdown) {
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, 0));
  } else if (color == "weis") {
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));
  } else if (color == "rot") {
    pixels.setPixelColor(n, pixels.Color(0, brightness, 0, 0));
  } else if (color == "grün") {
    pixels.setPixelColor(n, pixels.Color(brightness, 0, 0, 0));
  } else if (color == "blau") {
    pixels.setPixelColor(n, pixels.Color(0, 0, brightness, 0));
  } else if (color == "violett") {
    pixels.setPixelColor(n, pixels.Color(153, 50, 204, 0));
  } else if (color == "gelb") {
    pixels.setPixelColor(n, pixels.Color(brightness, brightness, 0, 0));
  } else {
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));
  }

  // pixels.clear();
  // if (inputMessage1 == "heart")
  //   heart();
  // 
  // if(inputMessage1 == "Kati")
  //   kati();
  // 
  // if(inputMessage1 == "Andi")
  //   andi();
  // 
  // if(inputMessage1 == "KatiAndi")
  //   katiAndi();
  // 
  // if (inputMessage1 == "Wilma")
  //   wilma();
}

void vor() {
  leuchten(41);
  leuchten(42);
  leuchten(43);
}

void nach() {
  leuchten(33);
  leuchten(34);
  leuchten(35);
  leuchten(36);
}

void fuenf() {
  leuchten(25);
  leuchten(24);
  leuchten(23);
  leuchten(22);
}

void zehn() {
  leuchten(32);
  leuchten(31);
  leuchten(30);
  leuchten(29);
}

void viertl() {
  leuchten(15);
  leuchten(16);
  leuchten(17);
  leuchten(18);
  leuchten(19);
  leuchten(20);
}

void halb() {
  leuchten(54);
  leuchten(53);
  leuchten(52);
  leuchten(51);
}

void dreiviertl() {
  leuchten(11);
  leuchten(12);
  leuchten(13);
  leuchten(14);
  leuchten(15);
  leuchten(16);
  leuchten(17);
  leuchten(18);
  leuchten(19);
  leuchten(20);
}

void oise() {
  leuchten(55);
  leuchten(56);
  leuchten(57);
  leuchten(58);
}

void zwoie() {
  leuchten(76);
  leuchten(75);
  leuchten(74);
  leuchten(73);
  leuchten(72);
}

void dreie() {
  leuchten(77);
  leuchten(78);
  leuchten(79);
  leuchten(80);
  leuchten(81);
}

void viere() {
  leuchten(105);
  leuchten(106);
  leuchten(107);
  leuchten(108);
  leuchten(109);
}

void fuenfe() {
  leuchten(49);
  leuchten(48);
  leuchten(47);
  leuchten(46);
  leuchten(45);
}

void sechse() {
  leuchten(57);
  leuchten(58);
  leuchten(59);
  leuchten(60);
  leuchten(61);
  leuchten(62);
}

void siebne() {
  leuchten(99);
  leuchten(100);
  leuchten(101);
  leuchten(102);
  leuchten(103);
  leuchten(104);
}

void achte() {
  leuchten(71);
  leuchten(70);
  leuchten(69);
  leuchten(68);
  leuchten(67);
}

void neune() {
  leuchten(95);
  leuchten(94);
  leuchten(93);
  leuchten(92);
  leuchten(91);
}

void zehne() {
  leuchten(98);
  leuchten(97);
  leuchten(96);
  leuchten(95);
  leuchten(94);
}

void elfe() {
  leuchten(62);
  leuchten(63);
  leuchten(64);
  leuchten(65);
}

void zwoelfe() {
  leuchten(82);
  leuchten(83);
  leuchten(84);
  leuchten(85);
  leuchten(86);
  leuchten(87);
}

void es_isch() {
  leuchten(10);
  leuchten(9);

  leuchten(7);
  leuchten(6);
  leuchten(5);
  leuchten(4);
}

void displayCorners(uint8_t a_corners) {
  static bool clear = 0;

  if (a_corners == 0 && clear) {
    pixels.clear(); //immer wenn eine neue 5min Phase beginnt, wird die Anzeige der Uhr aktualisiert
    clear = false; //clearVal wird auf 1 gesetzt, damit das Display bei vollen 5min nicht schnell blinkt, da es immer wider aktualisiert wird
  }

  if (a_corners == 1) {
    leuchten(112);
    clear = true; //clearVal wird für den nähsten Zyklus wieder auf 0 gesetzt
  }
  
  if (a_corners == 2) {
    leuchten(112);
    leuchten(111);
  }
  
  if (a_corners == 3) {
    leuchten(112);
    leuchten(111);
    leuchten(110);
  }
  
  if (a_corners == 4) {
    leuchten(112);
    leuchten(111);
    leuchten(110);
    leuchten(113);
  }
}

void displayMinutes(uint8_t a_minute) {
  if (a_minute >= 5 && a_minute < 10) {
    fuenf();
    nach();
  }

  if (a_minute >= 10 && a_minute < 15) {
    zehn();
    nach();
  }

  if (a_minute >= 15 && a_minute < 20) {
    viertl();
  }

  if (a_minute >= 20 && a_minute < 25) {
    zehn();
    vor();
    halb();
  }

  if (a_minute >= 25 && a_minute < 30) {
    fuenf();
    vor();
    halb();
  }

  if (a_minute >= 30 && a_minute < 35) {
    halb();
  }

  if (a_minute >= 35 && a_minute < 40) {
    fuenf();
    nach();
    halb();
  }

  if (a_minute >= 40 && a_minute < 45) {
    zehn();
    nach();
    halb();
  }

  if (a_minute >= 45 && a_minute < 50) {
    dreiviertl();
  }

  if (a_minute >= 50 && a_minute < 55) {
    zehn();
    vor();
  }

  if (a_minute >= 55 && a_minute < 60) {
    fuenf();
    vor();
  }
}

void displayHour(uint8_t a_hour) {
  if (a_hour == 0) zwoelfe();
  if (a_hour == 1) oise();
  if (a_hour == 2) zwoie();
  if (a_hour == 3) dreie();
  if (a_hour == 4) viere();
  if (a_hour == 5) fuenfe();
  if (a_hour == 6) sechse();
  if (a_hour == 7) siebne();
  if (a_hour == 8) achte();
  if (a_hour == 9) neune();
  if (a_hour == 10) zehne();
  if (a_hour == 11) elfe();
  if (a_hour == 12) zwoelfe();
}

inline uint8_t hoursToDisplay(uint8_t a_hour, uint8_t a_minute) {
  uint8_t hour = a_hour;
  if (a_minute > 15)
    hour++;
  if (hour > 12)
    hour -= 12;
  return hour;
}

void displayTime(Time a_time) {
  displayCorners(a_time.minute % 5);
  es_isch();
  displayMinutes(a_time.minute);
  displayHour(hoursToDisplay(a_time.hour, a_time.minute));
  pixels.show();
}