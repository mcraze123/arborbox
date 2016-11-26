/* AMBI101 Light Sensor Library
 * Author : Michael Craze
 * April 1st, 2013
 */

#ifndef ambi101_h
#define ambi101_h

#include "Arduino.h"

/* the number of samples to take before averaging value */
#define N_SAMPLES 100

/* the delay to take samples */
#define SAMPLE_RATE 1

class ambi101 {
	public:
		float read(int pin);
		float readAverage(int pin1, int pin2);
};

extern ambi101 lightSensor;

#endif
