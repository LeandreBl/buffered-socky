#include "buffered_socky.h"

void buffered_socky_destroy(struct buffered_socky *bsocky) {
    buffy_destroy(&bsocky->buffy_reader);
    buffy_destroy(&bsocky->buffy_writer);
    socky_destroy(&bsocky->socky);
}