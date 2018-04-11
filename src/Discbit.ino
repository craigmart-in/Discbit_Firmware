/*
 * Project Discbit
 * Description:
 * Author:
 * Date:
 */

#include "Adafruit_BluefruitLE_UART.h"
#include "ble.h"
#include "9dof.h"
#include "discData.h"

Adafruit_BluefruitLE_UART ble(&Serial1, BLUEFRUIT_UART_MODE_PIN);
DiscData discData;

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(115200);
  Wire.begin();
  // wait to allow for serial monitor.
  delay(1000);

  setupBle(ble);
  setup9dof();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //if (ble.isConnected()) {
    collect9dofData(discData);
    ble.println(discData.generateJson());
  //}
}
