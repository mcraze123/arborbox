#include <moistureSensor.h>
#include "printf.h"

void setup() {
	Serial.begin(9600);
	printf_begin();
}

void loop() {
	// reads analog pin A0 and returns the moisture percentage
	printf("Moisture = %d\n", ms.read(0));
}
