#include "Arduino.h"
#include "ambi101.h"

/*
 * input: analog pin number
 * output: light sensor value in lux
 */

float ambi101::read(int pin){
	float avg=0;
	for(int i=0;i < N_SAMPLES; i++){
		avg += (0.4743 * exp(0.0123 * analogRead(pin))) / N_SAMPLES;
		delay(SAMPLE_RATE);
	}
	return avg;
}

float ambi101::readAverage(int pin1, int pin2){
	float avg1=0;
	float avg2=0;
	for(int i=0; i < N_SAMPLES; i++){
		avg1 += (0.4743 * exp(0.0123 * analogRead(pin1))) / N_SAMPLES;
		avg2 += (0.4743 * exp(0.0123 * analogRead(pin2))) / N_SAMPLES;
		delay(SAMPLE_RATE);
	}
	return (avg1 + avg2) / 2;
}

ambi101 lightSensor;
