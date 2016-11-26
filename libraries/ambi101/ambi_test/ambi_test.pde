
void setup() {
	Serial.begin(9600);
}

void loop() {
	// reads analog pin A0, prints ambient light in lx
	Serial.print("Light = ");
	Serial.print(0.4743 * exp(0.0123 * analogRead(0)));
	Serial.println(" lx");
}

