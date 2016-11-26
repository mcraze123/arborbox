


#include <OneWire.h>
#include <DallasTemperature.h>
#include <dtwrapper.h>

DTWrapperClass tempSensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
   
  Serial.print("Temperature=");
  Serial.println(tempSensor.getTempC(2));
  
}

