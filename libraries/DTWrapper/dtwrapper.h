/*   

Dallas Temperature Sensor Wrapper 

*/

#ifndef DTWrapper_h
#define DTWrapper_h

#include <OneWire.h>
#include <DallasTemperature.h>

class DTWrapperClass 

{
	public:
	float getTempC(int pin);
	void printAddress(DeviceAddress deviceAddress);
};

#endif