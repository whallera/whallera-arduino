/*
  Whallera.h - Library for the Whallera MP1
  Created by Dario Salerno, February 2, 2011.
  Released into the public domain.
*/
#define Whallera_Debug 1

#ifndef Whallera_h
#define Whallera_h

#include <Arduino.h>
#include <Wire.h>

#define WHALLERA_STARTBYTE 0xaa
#define WHALLERA_STOPBYTE  0x55
#define WHALLERA_I2C_ADDR  0x69

//Commands
#define WHALLERA_READ_BANK 0x10
#define WHALLERA_WRITE_BANK 0x11
#define WHALLERA_DEVICE_LOCKED 0x20
#define WHALLERA_DEVICE_LOCK 0x21
#define WHALLERA_DEVICE_UNLOCK 0x22
#define WHALLERA_SET_PHRASE 0x23
#define WHALLERA_OPERATING_MODE 0x2e
#define WHALLERA_FACTORY_RESET 0x2f
#define WHALLERA_LED_CONF_SET 0x30
#define WHALLERA_VERSION 0x3f
#define WHALLERA_EXEC_ZENCODE 0x40
#define WHALLERA_EXEC_ZENCODE_STATUS 0x41

//Operating modes
#define WHALLERA_DEVELOPMENT 0x00
#define WHALLERA_PROGRAMMING 0xfe
#define WHALLERA_PRODUCTION 0xff 

//Led configuration
#define WHALLERA_LED_ALWAYS_OFF 0x00
#define WHALLERA_LED_ALWAYS_ON 0x01
#define WHALLERA_LED_BLINK_ON_ZENCODE 0x02
#define WHALLERA_LED_BLINK_ON_SERIAL 0x03

//Status codes
#define WHALLERA_OK 0x00
#define WHALLERA_CHECKSUM_ERROR 0x01
#define WHALLERA_DEVICE_LOCKED 0x11
#define WHALLERA_BANK_LOCKED 0x12
#define WHALLERA_BANK_OVERFLOW 0x20
#define WHALLERA_WAIT 0x33

//Zenroom Exit codes
#define WHALLERA_OK 0x00
#define WHALLERA_ERROR 0x01


class Whallera {
    public:
        void begin();
        uint8_t read_bank(uint8_t bank_id, char* bank_buffer, size_t bank_buffer_size);
        uint8_t write_bank(uint8_t bank_id, char* bank_buffer, size_t bank_buffer_size);
        uint8_t device_locked();
        uint8_t device_lock();
        uint8_t device_unlock(uint32_t phrase, uint8_t * remaining_attempts);
        uint8_t set_phrase(uint32_t phrase);
        uint8_t operating_mode(uint8_t mode);
        uint8_t factory_reset();
        uint8_t led_conf_set(uint8_t conf);
        uint8_t version(char * version); //TBD
        uint8_t exec_zencode(uint8_t script_bank_id,uint8_t keys_bank_id,uint8_t data_bank_id,uint8_t stdout_bank_id,uint8_t stderr_bank_id);
        uint8_t exec_zencode_status(uint8_t * zencode_status);
        
    private:
        uint8_t write_read(uint8_t cmd, char* write_buffer, size_t write_buffer_size, char* read_buffer, size_t read_buffer_size);
        void little_int16(uint16_t i, char *buffer);
        void little_int32(uint32_t i, char *buffer);
};

#endif
