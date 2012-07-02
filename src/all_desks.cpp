#include "../include/all_desks.h"

all_desks::all_desks() {
    //ctor
}

all_desks::~all_desks() {
    desks.clear();
}

void all_desks::set(int number) {
    desk newdesk;
    for(int i=1; i<=number; i++) {
        desks.push_back(newdesk);
    }
}

void all_desks::open(int number) {
    all_desks::set(number);
}

void all_desks::close(int number) {
    // this function needs to be carefully set
}

bool all_desks::is_free(double time_now) {
    desk newdesk;
    for (list<desk>::iterator it = desks.begin(); it != desks.end(); it++) {
        newdesk = *it;
        double finish_time = newdesk.get_finish();
        if(time_now >= finish_time) return true;
    }
    return false;
}

double all_desks::get_first_free() {

    desk newdesk = desks.front();
    double freetime = newdesk.get_finish();

    for (list<desk>::iterator it = desks.begin(); it != desks.end(); it++) {
        newdesk = *it;
        double finish_time = newdesk.get_finish();
        if(freetime > finish_time) freetime = finish_time;
    }
    return freetime;
}

bool all_desks::launch(double finish, double time_now) {

     for (list<desk>::iterator it = desks.begin(); it != desks.end(); it++) {
        desk temp = *it;
        if (time_now >= temp.get_finish()) {
            temp.set(finish);
            *it = temp;
            return true;
        }
     }
     return false;
}
