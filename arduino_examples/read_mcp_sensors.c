 /*
   int sensorValue = analogRead(A0);
   Serial.print(sensorValue);
   Serial.print("\n");
  */

#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp1;
//Adafruit_MCP23017 mcp2;

const byte GPIOA = 0x12; //Register address of port A
const byte GPIOB = 0x13; //Register address of port B
byte input=0;

void setup()
{
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
 
   mcp1.begin(0);
  // mcp2.begin(1);
 
   mcp1.pinMode(0, OUTPUT);
   mcp1.pinMode(1, OUTPUT);
   mcp1.pinMode(2, OUTPUT);
   mcp1.pinMode(3, OUTPUT);
   mcp1.pinMode(4, OUTPUT);
   mcp1.pinMode(5, OUTPUT);
   mcp1.pinMode(6, OUTPUT);

  // blink led
   mcp1.pinMode(7, OUTPUT);
   //mcp2.pinMode(7, OUTPUT);
  // sensor wired to A0
   mcp1.pinMode(8, OUTPUT);

   mcp1.pinMode(9, OUTPUT);
   mcp1.pinMode(10, OUTPUT);
   mcp1.pinMode(11, OUTPUT);
   mcp1.pinMode(12, OUTPUT);
   mcp1.pinMode(13, OUTPUT);
   mcp1.pinMode(14, OUTPUT);
   mcp1.pinMode(15, OUTPUT);

   mcp1.digitalWrite(7, LOW);
}

void turnOnLED() {
  mcp1.digitalWrite(7, HIGH);
}

void turnOffLED() {
  mcp1.digitalWrite(7, LOW);
}

void readSensor() {
  /*
  for (int i = 5; i <= 7; i++) {
    Serial.print("Turning on pin: ");
    Serial.println(i);
    mcp1.digitalWrite(i, HIGH);
    //delay(30);
    //int sensorValue = analogRead(A0);
    //Serial.println(sensorValue);
    delay(1000);
    mcp1.digitalWrite(i, LOW);
  }
  delay(1000);
  */
  /*
  mcp1.digitalWrite(7, HIGH);
  delay(1000);
  mcp1.digitalWrite(7, LOW);
  //mcp2.digitalWrite(7, HIGH);
  delay(1000);
  //mcp2.digitalWrite(7, LOW);
  */

  for (int i = 8; i <= 15; i++) {
    Serial.print("Turning on pin: ");
    Serial.println(i);
    mcp1.digitalWrite(i, HIGH);
    delay(30);
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    mcp1.digitalWrite(i, LOW);
    delay(500);
  }
  //Serial.println(mcp1.digitalRead(8)); 
  
}

void loop()
{
/*
  for (int i = 0; i<16; i++) {
    input = mcp1.digitalRead(i);
    if (input > 0) {
    Serial.print("Pin # ");
    Serial.print(i);
    Serial.print("\n");
    Serial.print(input);
    Serial.print("\n");
    }
  }
*/
  readSensor();
  //turnOnLED();
  //delay(500);
  //turnOffLED();
  //delay(500);
}