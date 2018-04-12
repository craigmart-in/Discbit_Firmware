/*
Source: https://learn.adafruit.com/introducing-the-adafruit-bluefruit-le-uart-friend/wiring
Source: https://github.com/rickkas7/Adafruit_BLE
Source: https://github.com/CollinCunningham/BLE_UART_Controller_Test/blob/master/BLE_UART_Controller_Test.ino


MOD - D3
CTS - Must connect to GND!
TXD - Connect to Photon/Electron RX pin
RXI - Connect to Photon/Electron TX pin
VIN - Connect to 3V3
RTS - No connection
GND - Connect to GND
DFU - No connection

*/

// COMMON SETTINGS
// ----------------------------------------------------------------------------------------------
// These settings are used in both SW UART, HW UART and SPI mode
// ----------------------------------------------------------------------------------------------
#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output

// HARDWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the HW serial port you are using. Uncomment
// this line if you are connecting the BLE to Leonardo/Micro or Flora
// ----------------------------------------------------------------------------------------------
#ifdef Serial1    // this makes it not complain on compilation if there's no Serial1
  #define BLUEFRUIT_HWSERIAL_NAME      &Serial1
#endif


// SHARED UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following sets the optional Mode pin, its recommended but not required
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_UART_MODE_PIN        D2    // Set to -1 if unused
