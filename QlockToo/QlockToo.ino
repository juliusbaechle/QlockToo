#include "soc/rtc_cntl_reg.h"
#include "Specials.h"
#include "GermanDisplay.h"
#include "QlockToo.h"
#include "QlockTooServer.h"

GermanDisplay display(specials, false);
QlockToo qlock(display);
QlockTooServer server(qlock);

void setup() {
  Serial.begin(115200);
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  qlock.initialize();
  server.initialize();
}

void loop() {
  qlock.update();
  server.update();
  delay(5);
}
