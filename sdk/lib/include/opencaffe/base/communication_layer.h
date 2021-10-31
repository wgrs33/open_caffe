#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

namespace OpenCaffe {

typedef struct {
    uint8_t priority : 2;
    uint8_t id : 6;
    uint16_t reftime;
    uint8_t message[20];
    uint8_t crc;
} DataPacket;

} // namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H