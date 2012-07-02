#include "../include/desk.h"

desk::desk() {
    finish_time = 0;
    n_clients = 0;
}

desk::~desk() {
    //dtor
}

void desk::set(double finish) {
    finish_time = finish;
    n_clients += 1;
}

double desk::get_finish() {
    return finish_time;
}

bool desk::is_free(double time_now) {
    if (time_now > finish_time) return true;
    else return false;
}

int desk::get_nclients() {
    return n_clients;
}
