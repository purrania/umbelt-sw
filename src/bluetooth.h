#include <bluefruit.h>
#include <string.h>
#include "Arduino.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

//    READ_BUFSIZE            Size of the read buffer for incoming packets
#define READ_BUFSIZE                    (20)

struct BLEInterface {
    // OTA DFU service
    BLEDfu bledfu;

    // Uart over BLE service
    BLEUart bleuart;
};

void init_bluetooth(BLEInterface *ble);

void bluetooth_read(BLEInterface *ble);

void startAdv(BLEInterface *ble);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

uint8_t readPacket(BLEUart *ble_uart, uint16_t timeout);
