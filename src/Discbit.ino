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
