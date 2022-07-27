#include "buffered_socky.h"

int buffered_socky_create(struct buffered_socky *bsocky, const struct buffered_socky_params *params) {
    if (socky_create(&bsocky->socky, params->protocol) == -1
        || buffy_create(&bsocky->buffy_reader, params->buffy_reader_capacity, params->buffy_reader_allocation_strategy) == -1
        || buffy_create(&bsocky->buffy_writer, params->buffy_writer_capacity, params->buffy_writer_allocation_strategy) == -1) {
        return -1;
        }
    return 0;
}