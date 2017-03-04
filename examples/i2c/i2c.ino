/***

	i2c.ino:	Bitlash I2C Demo (Master)

  Copyright (C) 2017 Andreas Wurf

	Bitlash Copyright (C) 2008-2012 Bill Roy

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.

***/

#include <string.h>

#include "Arduino.h"
#include "Wire.h"

#include "bitlash.h"
#include "src/bitlash.h"

// ----------------------------------------------------------------

// arg1: I2C slave address
// arg2..argN: data (mixed numbers(0..255) and strings)
static numvar i2c_write_impl (bool stop) {
  const auto argc = getarg (0);
  if (argc >= 2) {
    const auto address = getarg (1);
    Wire.beginTransmission ((uint8_t)address);
    for (numvar i = 2; i <= argc; i++) {
      if (isstringarg (i)) {
        auto text = (const char *)getstringarg (i);
        Wire.write (text, strlen (text));
      }
      else {
        Wire.write (getarg (i));
      }
    }
    Wire.endTransmission (stop);
  }
  return 0;
}

// ----------------------------------------------------------------

// arg1: I2C slave address
// arg2: quantity
// arg3*: internal address
// arg4*: internal address size in bytes
static numvar i2c_read_impl (bool stop) {
  const auto argc = getarg (0);
  if (argc >= 2) {
    const auto address = getarg (1);
    const auto quantity = getarg (2);
    numvar iaddress = 0, isize = 0;
    if (argc >= 3) {
      iaddress = getarg (3);
      isize = argc >= 4 ? getarg (4) : 1;
      if (isize == 0) {
        isize = 1;
      }
    }
    Wire.requestFrom (address, quantity, iaddress, isize, stop);
    while (Wire.available()) {
      sp ("0x");
      printIntegerInBase (Wire.read (), 16, 2, '0');
      if (Wire.peek() != -1) {
        spb (',');
      }
    }
    speol ();
  }
  return 0;
}

// ----------------------------------------------------------------

numvar i2c_writeln (void) {
  return i2c_write_impl (true);
}

// ----------------------------------------------------------------

numvar i2c_write (void) {
  return i2c_write_impl (false);
}

// ----------------------------------------------------------------

numvar i2c_read (void) {
  return i2c_read_impl (false);
}

// ----------------------------------------------------------------

numvar i2c_readln (void) {
  return i2c_read_impl (true);
}
// ----------------------------------------------------------------

void setup(void) {
  Wire.begin ();
  
	initBitlash(57600);		// must be first to initialize serial port

  // TODO: Add I2C related Bitlash functions here.
  addBitlashFunction ("i2cWrite", (bitlash_function) i2c_write);
  addBitlashFunction ("i2cWriteln", (bitlash_function) i2c_writeln);
  addBitlashFunction ("i2cRead", (bitlash_function) i2c_read);
  addBitlashFunction ("i2cReadln", (bitlash_function) i2c_readln);
}

void loop(void) {
	runBitlash();
}

// ----------------------------------------------------------------

