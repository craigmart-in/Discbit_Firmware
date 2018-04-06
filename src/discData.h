#ifndef _DISCDATA_H_
#define _DISCDATA_H_

#include "application.h"

class DiscData {
private:
    float _ax, _ay, _az;
    float _gx, _gy, _gz;
    float _mx, _my, _mz;
    float _yaw, _pitch, _roll;

public:
    void initDiscData(float ax, float ay, float az,
               float gx, float gy, float gz,
               float mx, float my, float mz,
               float yaw, float pitch, float roll);

    String generateJson();
};

#endif // _DISCDATA_H
