#include "Whallera.h"
#include <Wire.h>

void Whallera::begin(){
    Wire.begin();
}

uint8_t Whallera::read_bank(uint8_t bank_id, char* bank_buffer, size_t bank_buffer_size){

    char write_buffer[1];
    write_buffer[0] = bank_id;
    
    uint8_t status = write_read(WHALLERA_READ_BANK, write_buffer, sizeof(write_buffer), bank_buffer, bank_buffer_size);

    return status;
}

uint8_t Whallera::write_bank(uint8_t bank_id, char* bank_buffer, size_t bank_buffer_size){
    
    char write_buffer[bank_buffer_size + 3];
    char *p = write_buffer + 1;
    
    write_buffer[0] = bank_id;
    little_int16(bank_buffer_size, p);
    
    for(size_t i = 0; i < bank_buffer_size; i ++ ){
      write_buffer[ i + 3 ] = bank_buffer [ i ];
    }
    
    uint8_t status = write_read(WHALLERA_WRITE_BANK, bank_buffer, bank_buffer_size, 0, 0);

    return status;
}

uint8_t Whallera::device_locked(){

    uint8_t status = write_read(WHALLERA_DEVICE_LOCKED, 0, 0, 0, 0);

    return status;
}

uint8_t Whallera::device_lock(){

    uint8_t status = write_read(WHALLERA_DEVICE_LOCK, 0, 0, 0, 0);

    return status;
}

uint8_t Whallera::device_unlock(uint32_t phrase, uint8_t * remaining_attempts){

    char write_buffer[4];
    little_int32(phrase, write_buffer);
    
    uint8_t status = write_read(WHALLERA_DEVICE_UNLOCK, write_buffer, sizeof(write_buffer), remaining_attempts, 1);

    return status;
}

uint8_t Whallera::set_phrase(uint32_t phrase){
    char write_buffer[4];
    little_int32(phrase, write_buffer);
    
    uint8_t status = write_read(WHALLERA_SET_PHRASE, write_buffer, sizeof(write_buffer), 0, 0);

    return status;
}

uint8_t Whallera::operating_mode(uint8_t mode){

    uint8_t status = write_read(WHALLERA_OPERATING_MODE, &mode, 1, 0, 0);

    return status;
}

uint8_t Whallera::factory_reset(){

    uint8_t status = write_read(WHALLERA_FACTORY_RESET, 0, 0, 0, 0);

    return status;
}

uint8_t Whallera::led_conf_set(uint8_t conf){
  
    uint8_t status = write_read(WHALLERA_LED_CONF_SET, &conf, 1, 0, 0);

    return status;
}

uint8_t Whallera::version(char * version){

    uint8_t status = write_read(WHALLERA_VERSION, 0, 0, 0, 0);

    return status;
} //TBD

uint8_t Whallera::exec_zencode(uint8_t script_bank_id,uint8_t keys_bank_id,uint8_t data_bank_id,uint8_t stdout_bank_id,uint8_t stderr_bank_id){

    char write_buffer[5];
    write_buffer[0] = script_bank_id;
    write_buffer[1] = keys_bank_id;
    write_buffer[2] = data_bank_id;
    write_buffer[3] = stdout_bank_id;
    write_buffer[4] = stderr_bank_id;
    
    uint8_t status = write_read(WHALLERA_EXEC_ZENCODE, write_buffer, sizeof(write_buffer), 0, 0);

    return status;
}

uint8_t Whallera::exec_zencode_status(uint8_t * zencode_status){

    uint8_t status = write_read(WHALLERA_EXEC_ZENCODE_STATUS, 0, 0, zencode_status, 1);

    return status;
}

uint8_t Whallera::write_read(uint8_t cmd, char* write_buffer, size_t write_buffer_size, char* read_buffer, size_t read_buffer_size){

    char *p = read_buffer;
    size_t i = 0;
    uint8_t status;
    
    Wire.beginTransmission(WHALLERA_I2C_ADDR);
    Wire.write(cmd);
    Wire.write(write_buffer, write_buffer_size);

    Wire.requestFrom(WHALLERA_I2C_ADDR, read_buffer_size + 1);
    while(Wire.available()){
      if( i == 0 ){
        status = Wire.read();
      }
      else{
        p = read_buffer + i - 1;
        *p = Wire.read();
        
      }
      i += 1;
    }

}


void little_int16(uint16_t i, char *buffer){
  char *p;
  p = buffer;
  *p = ( i >> 8 ) & 0xff;
  p = buffer + 1;
  *p = i & 0xff;
}

void little_int32(uint32_t i, char *buffer){
  char *p ;
  p = buffer;
  *p = ( i >> 24 ) & 0xff;
  p = buffer + 1;
  *p = ( i >> 16 ) & 0xff;
  p = buffer + 2;
  *p = ( i >> 8 ) & 0xff;
  p = buffer + 3;
  *p = i & 0xff;
}
