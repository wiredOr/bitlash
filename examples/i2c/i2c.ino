/***

	i2c.ino:	Bitlash I2C Demo

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

#include "Arduino.h"
#include "Wire.h"
#include "bitlash.h"

// ----------------------------------------------------------------

static numvar i2c_write_impl (bool stop) {
  const auto argc = getarg (0);
  if (argc >= 2) {
    const auto address = getarg (1);
    Wire.beginTransmission ((uint8_t)address);
    // TODO: Wire.write()
    Wire.endTransmission (stop);
  }
  return 0;
}

// ----------------------------------------------------------------

// arg1: I2C slave address
// arg2..argN: data
numvar i2c_writeln (void) {
  return i2c_write_impl (true);
}

// ----------------------------------------------------------------

// arg1: I2C slave address
// arg2..argN: data
numvar i2c_write (void) {
  return i2c_write_impl (false);
}

// ----------------------------------------------------------------

void setup(void) {
  Wire.begin ();
  
	initBitlash(57600);		// must be first to initialize serial port

  // TODO: Add I2C related Bitlash functions here.
  addBitlashFunction ("i2cWrite", (bitlash_function) i2c_write);
  addBitlashFunction ("i2cWriteln", (bitlash_function) i2c_writeln);
}

void loop(void) {
	runBitlash();
}

// ----------------------------------------------------------------

