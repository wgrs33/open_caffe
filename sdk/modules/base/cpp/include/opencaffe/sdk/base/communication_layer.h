#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

namespace OpenCaffe {

typedef struct {
    uint8_t msgid; // 2 MSB priority, 6 LSB msg id
    uint16_t reftime;
    uint8_t size;
    uint8_t message[20];
    uint8_t crc;
} DataPacket;

typedef enum { ALERT = 0x00, CONFIRM = 0x41, IN_OUT_CNT = 0x81, ANALOGS = 0x82 } MsgID;

} // namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H