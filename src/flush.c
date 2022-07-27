#include "buffered_socky.h"

ssize_t buffered_socky_flush(struct buffered_socky *bsocky)
{
    return buffered_socky_flushf(bsocky, 0);
}