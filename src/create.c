#include "buffered_socky.h"

int buffered_socky_create(struct buffered_socky *bsocky, const struct buffered_socket_params *params) {
    if (socky_create(&bsocky->socky, params->protocol) == -1
        || buffy_create(&bsocky->input_buffy, params->input_buffy_capacity, params->input_buffy_allocation_strategy) == -1
        || buffy_create(&bsocky->output_buffy, params->output_buffy_capacity, params->output_buffy_allocation_strategy) == -1) {
        return -1;
        }
    return 0;
}