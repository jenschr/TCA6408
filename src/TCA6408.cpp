/*
* Arduino Library for MAX6639 I2C 2-Chan PWM Fan/Temp Controller
*
* Copyright (C) 2015 RF Designs. All rights reserved.
*
* Author: Bob Frady <rfdesigns@live.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License v2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 021110-1307, USA.
*
* If you can't comply with GPLv2, alternative licensing terms may be
* arranged. Please contact RF Designs <rfdesigns@live.com> for proprietary
* alternative licensing inquiries.
*/

#if defined(SPARK)
  #include "application.h"
#else
  #include <Wire.h>
#endif

#include "TCA6408.h"


void TCA6408::begin(void)
{
  _address = TCA6408_ADDR2; // use default
  Wire.begin();
}

void TCA6408::begin(uint8_t addr)
{
  _address = addr;
  Wire.begin();
}


void TCA6408::writeByte(uint8_t data, uint8_t reg) {
  Wire.beginTransmission(_address);
  I2CWRITE((uint8_t) reg);
  I2CWRITE((uint8_t) data);
  Wire.endTransmission();

  return;
}

bool TCA6408::readByte(uint8_t *data, uint8_t reg) {
  Wire.beginTransmission(_address);
  I2CWRITE((uint8_t) reg);
  Wire.endTransmission();
  uint8_t timeout=0;

  Wire.requestFrom(_address, (uint8_t) 0x01);
  while(Wire.available() < 1) {
    timeout++;
    if(timeout > I2CTIMEOUT) {
      return(true);
    }
    delay(1);
  }

  *data = I2CREAD();
  return(false);
}

uint8_t TCA6408::readInput(uint8_t ch) {
  uint8_t inputState = 255;
  readByte(&inputState, TCA6408_INPUT);
  return(inputState);
}
