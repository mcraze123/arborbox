#include <ambi101.h>

void setup() {
	Serial.begin(9600);

	// turn on pin 2 for powering second ambi101
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
}

void loop() {
	// reads analog pin A0, prints ambient light in lx
	Serial.print("AMBI101=");
	Serial.println(lightSensor.read(0));
	
	// reads analog pin A0, and A1, averages them, and prints ambient light in lx	
	Serial.print("AMBI101_AVG=");
	Serial.println(lightSensor.readAverage(0,1));
}
