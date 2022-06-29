#include "buffered_socky.h"

void buffered_socky_destroy(struct buffered_socky *bsocky) {
    buffy_destroy(&bsocky->input_buffy);
    buffy_destroy(&bsocky->output_buffy);
    socky_destroy(&bsocky->socky);
}