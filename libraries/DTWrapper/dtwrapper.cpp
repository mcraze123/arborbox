
/* Dallas Temperature Wrapper Class */
#include <dtwrapper.h>

float DTWrapperClass::getTempC(int pin) {

	//
	// Initialize the bus and get the device address
	//
	OneWire oneWire(pin);
	DallasTemperature sensors(&oneWire);
	DeviceAddress deviceAddress;

	//
	// setup the device
	// it might make sense to move this to a begin method
	// in the future...
	//
	//unsigned long stimer = millis();
	sensors.begin();
	sensors.getAddress(deviceAddress,0);
	sensors.setResolution(deviceAddress, 9);
	//unsigned long newtime = millis() - stimer;
	//Serial.print("Time:");
	//Serial.println(newtime);



	sensors.requestTemperatures();

    float tempC = sensors.getTempC(deviceAddress);
    //Serial.print("Temp C: ");
    //Serial.println(tempC);
    //Serial.print(" Temp F: ");
    //Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit


	//printAddress(deviceAddress);



	return  sensors.getTempC(deviceAddress);
}


// function to print a device address
void DTWrapperClass::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

	