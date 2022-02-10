#include "Whallera.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.println("Whallera Init");
  Whallera whallera;
  whallera.begin();
  
  
  char buf[] = "CiaoCiaoCiao";
  uint8_t remaining_attempts, zencode_status, status, bank = 1;
  uint32_t phrase = 1234;
  char zc_version[32];
  
  

 
  Serial.println("--> Write Bank");
  
  Serial.print("Bank 0x");
  Serial.println(bank, HEX);
  Serial.println("Content =======");
  Serial.write(buf, sizeof(buf));
  Serial.write("\n");
  Serial.println("EOF");
  
  status = whallera.write_bank(bank, buf, sizeof(buf));
  Serial.print("Status: 0x");
  Serial.println(status, HEX);


  
  Serial.println("--> Read Bank");

  Serial.print("Bank 0x");
  Serial.println(bank, HEX);

  status = whallera.read_bank(bank, buf, sizeof(buf));
  
  Serial.print("Status: 0x");
  Serial.println(status, HEX);
  
  Serial.println("Content =======");
  Serial.write(buf, sizeof(buf));
  Serial.write("\n");
  Serial.println("EOF");
  
  Serial.println("--> Device Locked");
  status = whallera.device_locked();
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Device Lock");
  status = whallera.device_lock();
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Device Unlock");
  status = whallera.device_unlock(phrase, &remaining_attempts);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Set phrase");
  status = whallera.set_phrase(phrase);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Operating Mode");
  status = whallera.operating_mode(WHALLERA_DEVELOPMENT);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Factory Reset");
  status = whallera.factory_reset();
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Led Conf Set");
  status = whallera.led_conf_set(WHALLERA_LED_ALWAYS_ON);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Version");
  status = whallera.version(zc_version); //TBD
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Exec Zencode");
  status = whallera.exec_zencode(1, 2, 3, 4, 5);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

  Serial.println("--> Exec Zencode Status");
  status = whallera.exec_zencode_status(&zencode_status);
  Serial.print("Status: 0x");
  Serial.println(status, HEX);

}

void loop() {
  // put your main code here, to run repeatedly:

}
