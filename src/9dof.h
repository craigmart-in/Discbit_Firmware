#ifndef _DISCBIT_9DOF_H_
#define _DISCBIT_9DOF_H_

#include "discData.h"

/*
Hardware setup:
MPU9250 Breakout --------- Particle
3v3 --------------------- 3.3V
SDA ----------------------- D0
SCL ----------------------- D1
GND ---------------------- GND
*/

#define SerialDebug false  // Set to true to get Serial output for debugging

#define MPU9250_ADDRESS 0x68
#define EXPECTED_MP9250_WHO_AM_I 0x73

#define PUBLISH_INTERVAL 5000

void setup9dof();
void collect9dofData(DiscData &discData);

#endif // _DISCBIT_9DOF_H_
