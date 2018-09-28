#include "Arduino.h"

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

	for (;;) {

    if (Serial.available() > 0) {
      Serial.write("Hello Client");
    }

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
		if (serialEventRun) serialEventRun();
	}

	return 0;
}