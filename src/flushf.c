#include "buffered_socky.h"

ssize_t buffered_socky_flushf(struct buffered_socky *bsocky, int flags)
{
    ssize_t ret = socky_send(&bsocky->socky, bsocky->buffy_reader.data, bsocky->buffy_reader.size, flags);

    if (ret < 0) {
        return -1;
    }
    buffy_discard(&bsocky->buffy_reader, (size_t)ret);
    return ret;
}