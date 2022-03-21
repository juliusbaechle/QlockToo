#pragma once

#include <Adafruit_NeoPixel.h>

#define LED_PIN 18 //Pin des LED-Bands
#define NUMPIXELS 114 //Anzahl der LEDs
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_RGBW + NEO_KHZ800); //Inizialisierung der NeoPixels Bibliothek

void leuchten(int n) {
  if (currentTime == startupTime || currentTime == "0" + startupTime)
    shutdown = false;
  if (currentTime == shutdownTime || currentTime == "0" + shutdownTime)
    shutdown = true;

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

  pixels.show();

  // if (inputMessage1 == "heart") {
  //   pixels.clear();
  //   pixels.setPixelColor(104, pixels.Color(0, brightness, 0));
  //   pixels.setPixelColor(94, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(92, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(80, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(84, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(74, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(68, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(56, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(64, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(54, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(44, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(43, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(33, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(31, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(23, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(38, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(28, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(26, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(14, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(13, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(18, pixels.Color(0, brightness, 0, 0));
  //   pixels.setPixelColor(19, pixels.Color(0, brightness, 0, 0));
  // }
  // 
  // if(inputMessage1 == "Kati"){
  //   pixels.clear();
  //   pixels.setPixelColor(0, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(1, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(2, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(3, pixels.Color(0,0,  0, brightness));
  // }
  // 
  // if(inputMessage1 == "Andi"){
  //   pixels.clear();
  //   pixels.setPixelColor(37, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(38, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(39, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(40, pixels.Color(0,0,  0, brightness));
  // }
  // 
  // if(inputMessage1 == "KatiAndi"){
  //   pixels.clear();
  //   pixels.setPixelColor(0, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(1, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(2, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(3, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(37, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(38, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(39, pixels.Color(0,0,  0, brightness));
  //   pixels.setPixelColor(40, pixels.Color(0,0,  0, brightness));
  // }
  // 
  // if (inputMessage1 == "Wilma") {
  //   pixels.clear();
  //   pixels.setPixelColor(28, pixels.Color(0, 0, 0, brightness));
  //   pixels.setPixelColor(27, pixels.Color(0, 0, 0, brightness));
  //   pixels.setPixelColor(26, pixels.Color(0, 0, 0, brightness));
  //   pixels.setPixelColor(37, pixels.Color(0, 0, 0, brightness));
  //   pixels.setPixelColor(38, pixels.Color(0, 0, 0, brightness));
  // }

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

void es() {
  leuchten(10);
  leuchten(9);
}

void isch() {
  leuchten(7);
  leuchten(6);
  leuchten(5);
  leuchten(4);
}

void displayTime(int hours, int minutes, int seconds) {
  static bool clear = 0;

  if (minutes > 15)
    hours++;
  if (hours > 12)
    hours -= 12;

  int eckMin = minutes % 5;
  if (eckMin == 0 && clear) {
    pixels.clear(); //immer wenn eine neue 5min Phase beginnt, wird die Anzeige der Uhr aktualisiert
    clear = false; //clearVal wird auf 1 gesetzt, damit das Display bei vollen 5min nicht schnell blinkt, da es immer wider aktualisiert wird
  }
  if (eckMin == 1) {
    leuchten(112);
    clear = true; //clearVal wird für den nähsten Zyklus wieder auf 0 gesetzt
  }
  if (eckMin == 2) {
    leuchten(112);
    leuchten(111);
  }
  if (eckMin == 3) {
    leuchten(112);
    leuchten(111);
    leuchten(110);
  }
  if (eckMin == 4) {
    leuchten(112);
    leuchten(111);
    leuchten(110);
    leuchten(113);
  }

  es();
  isch();

  if (minutes >= 5 && minutes < 10) {
    fuenf();
    nach();
  }

  if (minutes >= 10 && minutes < 15) {
    zehn();
    nach();
  }

  if (minutes >= 15 && minutes < 20) {
    viertl();
  }

  if (minutes >= 20 && minutes < 25) {
    zehn();
    vor();
    halb();
  }

  if (minutes >= 25 && minutes < 30) {
    fuenf();
    vor();
    halb();
  }

  if (minutes >= 30 && minutes < 35) {
    halb();
  }

  if (minutes >= 35 && minutes < 40) {
    fuenf();
    nach();
    halb();
  }

  if (minutes >= 40 && minutes < 45) {
    zehn();
    nach();
    halb();
  }

  if (minutes >= 45 && minutes < 50) {
    dreiviertl();
  }

  if (minutes >= 50 && minutes < 55) {
    zehn();
    vor();
  }

  if (minutes >= 55 && minutes < 60) {
    fuenf();
    vor();
  }

  //Stunden-Anzeige wird zugewiesen
  if (hours == 1) oise();
  if (hours == 2) zwoie();
  if (hours == 3) dreie();
  if (hours == 4) viere();
  if (hours == 5) fuenfe();
  if (hours == 6) sechse();
  if (hours == 7) siebne();
  if (hours == 8) achte();
  if (hours == 9) neune();
  if (hours == 10) zehne();
  if (hours == 11) elfe();
  if (hours == 12) zwoelfe();
  if (hours == 0) zwoelfe();
}