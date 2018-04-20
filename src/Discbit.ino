/*
 * Project Discbit
 * Description: Reads data from the 9dof sensor and transmits the discData
 *              over bluetooth.
 * Author: Craig Martin
 * Date: 4-11-2018
 */

 /*=========================================================================
     APPLICATION SETTINGS
     MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
     MODE_LED_BEHAVIOUR        LED activity, valid options are
                               "DISABLE" or "MODE" or "BLEUART" or
                               "HWUART"  or "SPI"  or "MANUAL"
     -----------------------------------------------------------------------*/
     #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
     #define MODE_LED_BEHAVIOUR          "DISABLE"
 /*=========================================================================*/
#include "BluefruitConfig.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "9dof.h"
#include "discData.h"

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);
DiscData discData;

int LED = D7;
int mom_pin = D3;
bool light_on = false;
unsigned long light_on_time;
unsigned long last_ble_write;

// A small helper
void error(const char *err) {
  Serial.println(err);
  while (1) {
    Particle.process();
  }
}

void setupBle() {
  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  // Setup the BLE device for Discbit.
  ble.sendCommandCheckOK("AT+GAPDEVNAME=Discbit");
  ble.sendCommandCheckOK("AT+EDDYSTONEURL=https://discbits.com");
  ble.sendCommandCheckOK("AT+EddyStoneServiceEn=on");
  ble.sendCommandCheckOK("AT+EddyStoneBroadcast=0");

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
    Particle.process();
    delay(500);
  }

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Turn off beacon
  ble.sendCommandCheckOK("AT+EddyStoneBroadcast=0");

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
}

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(mom_pin, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);

  setupBle();
  setup9dof();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  collect9dofData(discData);

  if (millis() - last_ble_write > 500) {
    last_ble_write = millis();
    ble.println(discData.generateJson());
  }

  // Detect disc in basket
  int mom_state = 0;
  // perform digital reads (returns either 1 or 0 if it sees "HIGH" or "LOW" voltage)
  mom_state = digitalRead(mom_pin);

  if (mom_state == 1) {
    Particle.publish("disc-in-basket", "<put disc id here>", 60, PRIVATE);

    light_on = true;
    digitalWrite(LED, HIGH);
    light_on_time = millis();
  }

  if (light_on && (millis() - light_on_time > 2000)) {
    light_on = false;
    digitalWrite(LED, LOW);
  }
}
