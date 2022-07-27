#include "buffered_socky.h"

#define BUFFER_REALLOCATION_COEFFICIENT 2

ssize_t buffered_socky_recv(struct buffered_socky *bsocky, size_t size, int flags)
{
    int ret;
    ssize_t rd;

    if (bsocky->buffy_reader.flags == BUFFY_FIXED_SIZE_STRATEGY) {
        size = bsocky->buffy_reader.capacity - bsocky->buffy_reader.size;
    } else{
        ret = buffy_resize_capacity(&bsocky->buffy_reader, (((bsocky->buffy_reader.size + size) | 0x1) + 1) * BUFFER_REALLOCATION_COEFFICIENT);
        if (ret < 0) {
            return ret;
        }
    }
    rd = socky_recv(&bsocky->socky, &bsocky->buffy_reader.data[bsocky->buffy_reader.size], size, flags);
    if (rd < 0) {
        return rd;
    }
    bsocky->buffy_reader.size += rd;
    return rd;
}