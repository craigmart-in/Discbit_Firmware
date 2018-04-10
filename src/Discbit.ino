/*
 * Project Discbit
 * Description:
 * Author:
 * Date:
 */

#include "ble.h"
#include "9dof.h"

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(115200);
  Wire.begin();
  // wait to allow for serial monitor.
  delay(1000);

  setupBle();
  setup9dof();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  collect9dofData();
}
