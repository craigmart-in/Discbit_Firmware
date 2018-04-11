/*
Source: https://learn.adafruit.com/introducing-the-adafruit-bluefruit-le-uart-friend/wiring
Source: https://github.com/rickkas7/Adafruit_BLE
Source: https://github.com/CollinCunningham/BLE_UART_Controller_Test/blob/master/BLE_UART_Controller_Test.ino


MOD - Optional for changing between modes (see note below)
CTS - Must connect to GND!
TXD - Connect to Photon/Electron RX pin
RXI - Connect to Photon/Electron TX pin
VIN - Connect to 3V3
RTS - No connection
GND - Connect to GND
DFU - No connection

*/

#include "Adafruit_BluefruitLE_UART.h"

#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   false  // If set to 'true' enables debug output

/*=========================================================================
    APPLICATION SETTINGS                                                   */
    #define FACTORYRESET_ENABLE      0
/*=========================================================================*/

#define MODE_LED_BEHAVIOUR             "MODE"
#define BLUEFRUIT_UART_MODE_PIN	 	     -1   // not using, so set to -1

// A small helper
void error(const char *err);

void setupBle(Adafruit_BluefruitLE_UART &ble);

void getUserInput(char buffer[], uint8_t maxSize);
