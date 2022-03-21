#pragma once

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

void leuchten(int n) {
  if (onoffState == "ON") {

    if (farbe == "weis") {
      pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));
    }

    else if (farbe == "rot") {
      pixels.setPixelColor(n, pixels.Color(0, brightness, 0, 0));
    }

    else if (farbe == "grün") {
      pixels.setPixelColor(n, pixels.Color(brightness, 0, 0, 0));
    }
    else if (farbe == "blau") {
      pixels.setPixelColor(n, pixels.Color(0, 0, brightness, 0));
    }

    else if (farbe == "violett") {
      pixels.setPixelColor(n, pixels.Color(153, 50, 204, 0));
    }

    else if (farbe == "gelb") {
      pixels.setPixelColor(n, pixels.Color(brightness, brightness, 0, 0));
    }

    else {
      pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));
    }
  }

  if (onoffState == "OFF") {
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, 0));
  }

  if (farbe == "weis" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));

  }

  if (farbe == "rot" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(0, brightness, 0, 0));
  }

  if (farbe == "grün" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(brightness, 0, 0, 0));
  }
  if (farbe == "blau" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(0, 0, brightness, 0));
  }

  if (farbe == "violett" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(153, 50, 204, 0));
  }

  if (farbe == "gelb" && onoffState == "ON") {
    pixels.setPixelColor(n, pixels.Color(brightness, brightness, 0, 0));
  }



  if (clockstate == input2 || clockstate == "0" + input2) {

    timeout = "OFF";
  }

  if (clockstate == input1 || clockstate == "0" + input1) {
    timeout = "ON";
    onoffState = "ON";
    if (farbe == "weis") {
      pixels.setPixelColor(n, pixels.Color(0, 0, 0, brightness));
    }

    if (farbe == "rot") {
      pixels.setPixelColor(n, pixels.Color(0, brightness, 0, 0));
    }

    if (farbe == "grün") {
      pixels.setPixelColor(n, pixels.Color(brightness, 0, 0, 0));
    }
    if (farbe == "blau") {
      pixels.setPixelColor(n, pixels.Color(0, 0, brightness, 0));
    }

    if (farbe == "violett") {
      pixels.setPixelColor(n, pixels.Color(153, 50, 204, 0));
    }

    if (farbe == "gelb") {
      pixels.setPixelColor(n, pixels.Color(brightness, brightness, 0, 0));
    }

  }

  if (timeout == "OFF") {
    onoffState = "OFF";
    pixels.setPixelColor(n, pixels.Color(0, 0, 0, 0));
  }

  if (inputMessage1 == "heart") {
    pixels.clear();
    pixels.setPixelColor(104, pixels.Color(0, brightness, 0));
    pixels.setPixelColor(94, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(92, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(80, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(84, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(74, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(68, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(56, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(64, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(54, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(44, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(43, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(33, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(31, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(23, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(38, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(28, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(26, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(14, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(13, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(18, pixels.Color(0, brightness, 0, 0));
    pixels.setPixelColor(19, pixels.Color(0, brightness, 0, 0));
  }

  /*  if(inputMessage1=="Kati"){
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(1, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(2, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(3, pixels.Color(0,0,  0, brightness));
    }

    if(inputMessage1=="Andi"){
      pixels.clear();
      pixels.setPixelColor(37, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(38, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(39, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(40, pixels.Color(0,0,  0, brightness));
    }

    if(inputMessage1=="KatiAndi"){
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(1, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(2, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(3, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(37, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(38, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(39, pixels.Color(0,0,  0, brightness));
      pixels.setPixelColor(40, pixels.Color(0,0,  0, brightness));
    }
  */
  if (inputMessage1 == "Wilma") {
    pixels.clear();
    pixels.setPixelColor(28, pixels.Color(0, 0, 0, brightness));
    pixels.setPixelColor(27, pixels.Color(0, 0, 0, brightness));
    pixels.setPixelColor(26, pixels.Color(0, 0, 0, brightness));
    pixels.setPixelColor(37, pixels.Color(0, 0, 0, brightness));
    pixels.setPixelColor(38, pixels.Color(0, 0, 0, brightness));

  }

  pixels.show();
}