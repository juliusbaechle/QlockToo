#include "Specials.h"
#include "GermanDisplay.h"
#include "QlockToo.h"
#include "QlockServer.h"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

GermanDisplay display(specials);
QlockToo qlock(display);
QlockServer server(qlock);

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  qlock.initialize();
  server.initialize();
}

void loop() {
  qlock.update();
  server.update();
  delay(10);
}
