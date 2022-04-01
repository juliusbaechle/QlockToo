// TODO: Enhanced website stylesheets

#include "Specials.h"
#include "GermanDisplay.h"
#include "QlockToo.h"
#include "QlockServer.h"

GermanDisplay display(specials);
QlockToo qlock(display);
QlockServer server(qlock);

void setup() {
  Serial.begin(115200);
  qlock.initialize();
  server.initialize();
}

void loop() {
  qlock.update();
  server.update();
  delay(10);
}
