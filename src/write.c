#include "buffered_socky.h"

ssize_t buffered_socky_write(struct buffered_socky *bsocky, const void *data, size_t size)
{
    return buffy_write(&bsocky->buffy_reader, data, size);
}