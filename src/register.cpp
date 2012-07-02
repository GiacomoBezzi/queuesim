#include "../include/register.h"

register::register() {
    finish_time =  0;
    n_clients = 0;
}

register::~register() {
    //dtor
}

void register::set(double how_long, double time_now) {
    finish_time = time_now + how_long;
}
