/*
 * Project Discbit
 * Description:
 * Author:
 * Date:
 */

/*
Hardware setup:
MPU9250 Breakout --------- Particle
3v3 --------------------- 3.3V
SDA ----------------------- D0
SCL ----------------------- D1
GND ---------------------- GND
*/

#include "Adafruit_BluefruitLE_UART.h"

#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output

/*=========================================================================
    APPLICATION SETTINGS                                                   */
    #define FACTORYRESET_ENABLE      0
/*=========================================================================*/

#define MODE_LED_BEHAVIOUR             "MODE"
#define BLUEFRUIT_UART_MODE_PIN	 	     -1   // not using, so set to -1

Adafruit_BluefruitLE_UART ble(&Serial1, BLUEFRUIT_UART_MODE_PIN);

bool showPrompt = true;

// A small helper
void error(const char *err) {
  //Serial.println(err);
  while (1);
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(115200);
  // wait to allow for serial monitor.
  delay(1000);

  Serial.println(F("Adafruit Bluefruit AT Command Example"));
  Serial.println(F("-------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // Display command prompt
  Serial.print(F("AT > "));
  // Check for user input and echo it back if anything was found
  char command[BUFSIZE+1];
  getUserInput(command, BUFSIZE);

  // Send command
  ble.println(command);

  // Check response status
  ble.waitForOK();
}

void getUserInput(char buffer[], uint8_t maxSize)
{
  memset(buffer, 0, maxSize);
  while( Serial.available() == 0 ) {
    delay(1);
  }

  uint8_t count=0;

  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.available() == 0) );
}
