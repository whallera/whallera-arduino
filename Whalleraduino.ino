#include "Whallera.h"

int var = 0xff;

void setup() {
  Whallera whallera;
  whallera.begin();
  
  // put your setup code here, to run once:
  whallera.device_locked();

}

void loop() {
  // put your main code here, to run repeatedly:

}
