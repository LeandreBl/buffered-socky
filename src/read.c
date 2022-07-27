#include "buffered_socky.h"

ssize_t buffered_socky_read(struct buffered_socky *bsocky, size_t size)
{
    return buffered_socky_recv(bsocky, size, 0);
}