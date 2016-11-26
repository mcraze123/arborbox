#include "Arduino.h"
#include "moistureSensor.h"

/*
 * input: pin - analog pin number
 * output: moisture percentage
 */

int moistureSensor::read(int pin){
	int v;
	v=analogRead(pin);
	if(v < MS_MAX){
		return (int)((v/MS_MAX)*100.0);
	}
	else {
		return 100;
	}
}

moistureSensor ms;
