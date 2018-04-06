#include "application.h"
#include "discData.h"

void DiscData::initDiscData(float ax, float ay, float az,
               float gx, float gy, float gz,
               float mx, float my, float mz,
               float yaw, float pitch, float roll)
   {
       _ax = ax;
       _ay = ay;
       _az = az;

       _gx = gx;
       _gy = gy;
       _gz = gz;

       _mx = mx;
       _my = my;
       _mz = mz;

       _yaw = yaw;
       _pitch = pitch;
       _roll = roll;
   }

String DiscData::generateJson() {
    String payload = "{";
    payload += String::format("\"ax\": %f, \"ay\": %f, \"az\": %f",
        _ax, _ay, _az);
    payload += String::format("\"gx\": %f, \"gy\": %f, \"gz\": %f",
        _gx, _gy, _gz);
    payload += String::format("\"mx\": %f, \"my\": %f, \"mz\": %f",
        _mx, _my, _mz);
    payload += String::format("\"yaw\": %f, \"pitch\": %f, \"roll\": %f",
        _yaw, _pitch, _roll);
    payload += "}";

    return payload;
}
