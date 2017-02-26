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

numvar i2c_begin(void) {
  if (getarg(0)) {
    Wire.begin ((uint8_t)getarg(1));
  }
  else {
    Wire.begin ();
  }
	return 0;
}

// ----------------------------------------------------------------

numvar i2c_end(void) {
  Wire.end ();
  return 0;
}

// ----------------------------------------------------------------

numvar i2c_beginTransmission(void) {
  Wire.beginTransmission ((uint8_t)getarg(1));
}

// ----------------------------------------------------------------

numvar i2c_endTransmission(void) {
  if (getarg(0)) {
    Wire.endTransmission ((uint8_t)getarg(1));
  }
  else {
    Wire.endTransmission ();
  }
}

// ----------------------------------------------------------------

void setup(void) {
	initBitlash(57600);		// must be first to initialize serial port

	addBitlashFunction("i2cBegin", (bitlash_function) i2c_begin);
  addBitlashFunction("i2cEnd", (bitlash_function) i2c_end);
  addBitlashFunction("i2cTxBegin", (bitlash_function) i2c_beginTransmission);
  addBitlashFunction("i2cTxEnd", (bitlash_function) i2c_endTransmission);
}

void loop(void) {
	runBitlash();
}

// ----------------------------------------------------------------

