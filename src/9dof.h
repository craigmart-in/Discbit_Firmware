#ifndef _DISCBIT_9DOF_H_
#define _DISCBIT_9DOF_H_

#define AHRS true         // Set to false for basic data read
#define SerialDebug true  // Set to true to get Serial output for debugging

#define MPU9250_ADDRESS 0x68
#define EXPECTED_MP9250_WHO_AM_I 0x73

#define PUBLISH_TIME 5000

void setup9dof();
void collect9dofData();

#endif // _DISCBIT_9DOF_H_
