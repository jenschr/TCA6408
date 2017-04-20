#ifndef TCA6408_H
#define TCA6408_H


/* Retro-compatibility with arduino 0023 and previous version */
#if defined(SPARK)
  #include "application.h"
  #define I2CWRITE(x) Wire.write(x)
  #define I2CREAD() Wire.read()
#else
  #if ARDUINO >= 100
  #include "Arduino.h"
  #define I2CWRITE(x) Wire.write(x)
  #define I2CREAD() Wire.read()
  #else
  #include "WProgram.h"
  #define I2CWRITE(x) Wire.send(x)
  #define I2CREAD() Wire.receive()
  #endif
#endif

#include <inttypes.h>


#ifndef I2CTIMEOUT
  #define I2CTIMEOUT 100
#endif

 /* The TCA6408 has valid Addresses 0x20 and 0x20 */
 #define TCA6408_ADDR1                           0x20
 #define TCA6408_ADDR2                           0x21

/* Command bytes */
 #define TCA6408_INPUT                           0x00
 #define TCA6408_OUTPUT                          0x01
 #define TCA6408_POLARITY_INVERSION              0x02
 #define TCA6408_CONFIGURATION                   0x03


class TCA6408 {
public:
  void begin(void);
  void begin(uint8_t _address);
  void writeByte(uint8_t data, uint8_t reg);
  bool readByte(uint8_t *data, uint8_t reg);
  uint8_t readInput(uint8_t ch);

protected:

private:
  uint8_t _address;

 };

#endif
