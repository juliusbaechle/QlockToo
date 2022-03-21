//Bibliotheken 

//Wifi
#include <SPIFFS.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <AsyncTCP.h>



//LED Band
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            18 //Pin des LED-Bands

#define NUMPIXELS      114 //Anzahl der LEDs
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800); //Inizialisierung der NeoPixels Bibliothek

//Zeit aus dem Interne
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

#include <Timer.h>
#include <Wire.h>

Timer t;

#define DS3231_I2C_ADDRESS 0x68 //Adresse zur Kommunikation mit RTC



//Benutzername und Passwort für Eingabseite
const char* http_username = "admin";
const char* http_password = "admin";


int eckMin = 0; //Minutenvariable für Eck-LEDs
int clearVal = 0; //Variable zum aktualisieren der Uhr


// Benutzername und Passwort des WLANs
//const char* ssid = "WLAN-H9YLUN";
//const char* password = "2054471066375812";



const char* ssid = "AndroidAP";
const char* password = "Mi07022018kW";

//const char* ssid = "FRITZ!Box 7530 BV";
//const char* password = "50115224757008808357";

//const char* ssid = "FRITZ!Box 7412";
//const char* password = "50260940954024060443";




//Variablen für Helligkeitssteuerung
int brightness = 160;
String sliderValue = "255";

String farbe = "rot";

String onoffState = "ON";
String on_State = "-";
String off_State = "-";


//Variablen für Zeitsteuerung
String input1; //String um .00 von inputMessage erweitern
String input2;
const char* PARAM_INPUT = "value";
const char* PARAM_STRING = "inputString";
const char* PARAM_INPUT_3 = "state";

String inputMessage1;
String inputParam1;
String inputMessage2;
String inputParam2;
String automatic = "1";

int count1 = 0; //Versuche mit dem Internet zu verbinden


int tickEvent; //Tmer zur Aktualisierung
int hours;  //Stundenvariable
int minutes; //Minutenvariable

String clockstate;

String minuten;
String stunden;
String sekunden;
String timeout = "ON";


const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";



int eingang = 35; //Das Wort „eingang“ steht jetzt für den Wert „A0“ (Bezeichnung vom Analogport 0)
int sensorWert = 0;
int output = 150;
int helligkeit = 0;


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Website nach Betätigung des Logouts
const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <p>Logged out or <a href="/">return to homepage</a>.</p>
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";

// Replaces placeholder with LED state /Slidervalue value
String processor(const String& var) {

  if (var == "GPIO_STATE") {

    return onoffState;
  }

  if (var == "An_STATE") {

    return on_State;
  }
  if (var == "Aus_STATE") {

    return off_State;
  }

  if (var == "SLIDERVALUE") {

    return sliderValue;
  }
  return onoffState, on_State, sliderValue;

}

byte decToBcd(byte val)
{
  return ((val / 10 * 16) + (val % 10));
}

//konvertiert binären Code in Dezimalcode
byte bcdToDec(byte val)
{
  return ((val / 16 * 10) + (val % 16));
}


void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.endTransmission();
}

//konvertiert Dezimalcode in binären Code




void setup() {


  // Serial port for debugging purposes
  Serial.begin(115200);
  Wire.begin();
  tickEvent = t.every(1000, displayTime); //alle 1000ms wird displayTime ausgeführt


  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    count1 = ++count1;
    delay(500);
    Serial.print(".");
    Serial.print(count1);
    if (count1 == 15) {
      count1 = 0;
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    count1 = 0;
  }
  timeClient.begin();
  timeClient.update();

  if (WiFi.status() == WL_CONNECTED) {
    setDS3231time(timeClient.getSeconds(), timeClient.getMinutes(), timeClient.getHours(), timeClient.getDay());
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/style.css", "text/css");
    });

  server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    onoffState = "ON";
    timeout = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    onoffState = "OFF";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/white", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "weis";
    onoffState = "ON";
    timeout = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/red", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "rot";
    onoffState = "ON";
    timeout = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/grün", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "grün";
    onoffState = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/blau", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "blau";
    onoffState = "ON";
    timeout = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/violett", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "violett";
    onoffState = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/gelb", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    farbe = "gelb";
    onoffState = "ON";
    timeout = "ON";
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputParam1 = PARAM_INPUT_1;
      on_State = inputMessage1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;
      off_State = inputMessage2;
    }
    else {
      inputMessage1 = "No message sent";
      inputParam1 = "none";
    }



    server.on("/button9", HTTP_GET, [](AsyncWebServerRequest* request) {
      if (!request->authenticate(http_username, http_password))
        return request->requestAuthentication();
      on_State = "-";
      off_State = "-";
      timeout = "ON";
      onoffState = "ON";
      inputMessage1 = "Reset";
      inputMessage2 = "Reset";
      pixels.clear();
      request->send(SPIFFS, "/index.html", String(), false, processor);
      });



    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/slider", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
    }

    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_3)) {
      automatic = request->getParam(PARAM_INPUT_3)->value();
    }
    else {
      automatic = "No message sent";

    }
    Serial.print("GPIO: ");
    Serial.println(automatic);

    request->send(SPIFFS, "/index.html", String(), false, processor);
    });


  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(401);
    });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", logout_html, processor);
    });




  // Start server
  server.begin();
  pixels.show();
}

void readDS3231time(byte* second,
  byte* minute,
  byte* hour,
  byte* dayOfWeek
)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // gibt O Uhr vor
  Wire.endTransmission();

  //7 Bytes werden vom RTC abgefragt
  Wire.requestFrom(DS3231_I2C_ADDRESS, 4);
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek;
  readDS3231time(&second, &minute, &hour, &dayOfWeek);

  minutes = (minute)-0;
  if (minutes < 15) hours = (hour)-0;
  else hours = ((hour)-0) + 1;


  if (minute < 10) {
    minuten = "0" + String(minute);
  }
  else {
    minuten = String(minute);
  }

  if (hour < 10) {
    stunden = "0" + String(hour);
  }
  else {
    stunden = String(hour);
  }

  if (second < 10) {
    sekunden = "0" + String(second);
  }
  else {
    sekunden = String(second);
  }


  clockstate = stunden + "." + minuten + "." + sekunden;
  input2 = String(inputMessage2) + "." + "00";
  input1 = String(inputMessage1) + "." + "00";
  Serial.print("Zeit:");
  Serial.println(clockstate);
  Serial.print("input1:");
  Serial.print(input1);
  Serial.print("input2:");
  Serial.println(input2);
  Serial.print("sliderValue:");
  Serial.println(sliderValue);


  if (automatic == "1") {
    sensorWert = analogRead(eingang); //Die Spannung an dem Fotowiderstand auslesen und unter der Variable „sensorWert“ abspeichern.
    Serial.print("Sensorwert = "); //Ausgabe am Serial-Monitor: Das Wort „Sensorwert: „
    Serial.println(sensorWert); //Ausgabe am Serial-Monitor. Mit dem Befehl Serial.print wird der Sensorwert des Fotowiderstandes in Form einer Zahl zwischen 0 und 1023 an den serial monitor gesendet.
    output = map(sensorWert, 0, 2500, 0, 255);
    Serial.print("brightness = "); //Ausgabe am Serial-Monitor: Das Wort „Sensorwert: „
    Serial.println(brightness);

    if (sensorWert > 2500) {
      output = 255;
    }


    if (output < brightness - 5) {
      brightness = brightness - 5;
    }
    if (output > brightness + 5) {
      brightness = brightness + 5;
    }

    if (brightness < 30) {
      brightness = 30;
    }

    //sliderValue=String(brightness);
  }
  if (automatic == "0") {
    brightness = sliderValue.toInt();

  }

  Serial.print("brightness = "); //Ausgabe am Serial-Monitor: Das Wort „Sensorwert: „
  Serial.println(brightness);



  eckMin = minutes % 5; //Eckminuten werden aus Minuten geteilt durch 5 berechnet; der ganzzahlige Rest liegt somit zwischen 0 und 4
  if (eckMin == 0 && clearVal == 0) {
    pixels.clear(); //immer wenn eine neue 5min Phase beginnt, wird die Anzeige der Uhr aktualisiert
    clearVal = 1; //clearVal wird auf 1 gesetzt, damit das Display bei vollen 5min nicht schnell blinkt, da es immer wider aktualisiert wird
  }
  if (eckMin == 1) {
    leuchten(112); //die Funktion leuchten wird mit dem Parameter n aufgerufen; n steht fr die LED di leuchten soll
    clearVal = 0; //clearVal wird für den nähsten Zyklus wieder auf 0 gesetzt
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

  leuchten(10);
  leuchten(9);
  leuchten(7);
  leuchten(6);
  leuchten(5);
  leuchten(4);

  // Serial.println(minutes);

   //Zeitabschnitte zum Anzeigen von viertl, halb, dreiviertl, zehn, fünf, vor und nach werden definiert
  if (minutes >= 15 && minutes < 20) viertl();

  if (minutes >= 10 && minutes < 15) {
    zehn();
    nach();
  }
  if (minutes >= 5 && minutes < 10) {
    fuenf();
    nach();
  }

  if (minutes >= 30 && minutes < 35) halb();

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

  if (minutes >= 40 && minutes < 45) {
    zehn();
    nach();
    halb();
  }

  if (minutes >= 35 && minutes < 40) {
    fuenf();
    nach();
    halb();
  }

  if (minutes >= 45 && minutes < 50) dreiviertl();

  if (minutes >= 50 && minutes < 55) {
    zehn();
    vor();
  }

  if (minutes >= 55 && minutes < 60) {
    fuenf();
    vor();
  }

  //Stunden-Anzeige wird zugewiesen
  if (hours > 12) hours = hours - 12;
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

  //optional zur Ausgabe von Sekunden auf dem seriellen Monitor
  /*Serial.print(":");
    if (second<10)
    {
    Serial.print("0");
    }
    Serial.println(second, DEC);*/



  switch (dayOfWeek) {
  case 0:
    Serial.println("Sunday");
    break;
  case 1:
    Serial.println("Monday");
    break;
  case 2:
    Serial.println("Tuesday");
    break;
  case 3:
    Serial.println("Wednesday");
    break;
  case 4:
    Serial.println("Thursday");
    break;
  case 5:
    Serial.println("Friday");
    break;
  case 6:
    Serial.println("Saturday");
    break;
  }

  //WLAN Verbindung herstellen
  if (minute == 20 && second == 0) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      count1 = ++count1;
      delay(500);
      Serial.print(".");
      Serial.print(count1);
      if (count1 == 15) {
        count1 = 0;
        break;
      }
      if (WiFi.status() == WL_CONNECTED) {
        count1 = 0;
        Serial.print("wlan verbindung");
      }

    }
  }



  //Update RTC Sonntags um 5 Uhr
  if (dayOfWeek == 0 && hour == 5 && minute == 0 && second == 30) {
    while (WiFi.status() != WL_CONNECTED) {
      count1 = ++count1;
      delay(500);
      Serial.print(".");
      Serial.print(count1);
      if (count1 == 15) {
        count1 = 0;
        break;
      }
      if (WiFi.status() == WL_CONNECTED) {
        count1 = 0;
      }
      timeClient.update();
      setDS3231time(timeClient.getSeconds(), timeClient.getMinutes(), timeClient.getHours(), timeClient.getDay());
      Serial.print("wurde geupdatet");
    }

  }



}


void loop() {
  t.update();
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