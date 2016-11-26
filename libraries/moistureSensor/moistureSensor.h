/* Soil Moisture Sensor Library
 * Author: Michael Craze
 * April 1st, 2013
 */
#ifndef moistureSensor_h
#define moistureSensor_h

#include "Arduino.h"

// Maximum analog reading in water
#define MS_MAX 700.0

class moistureSensor {
	public:
		int read(int pin);
};

extern moistureSensor ms;

#endif
