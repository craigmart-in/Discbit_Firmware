#include "application.h"

void printAddress(byte address);

void i2c_setup() {
    Wire.begin();
    Serial.begin(9600);

    while (!Serial);

    Serial.println("I2C Scanner");
}

void i2c_loop() {
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            printAddress(address);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            printAddress(address);
        }
    }

    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    }
    else {
        Serial.println("Done.\n");
    }

    delay(5000);
}

void printAddress(byte address) {
    if (address < 16) Serial.print("0");
    Serial.println(address,HEX);
}
