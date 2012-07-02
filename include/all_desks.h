#ifndef ALL_DESKS_H
#define ALL_DESKS_H

#include "desk.h"
#include <list>
#include <stdlib.h>

using namespace std;

class all_desks
{
    public:
        all_desks();
        virtual ~all_desks();
        void set(int number); //standard set function
        void open(int number); // to add a new desk
        void close(int number); // to remove a desk NB: CAUTION!!
        bool launch(double finish, double time_now); // to launch a new agent returns true if succesfull
        bool is_free(double time_now);
        double get_first_free();
    protected:
    private:
        list<desk> desks;
};

#endif // ALL_DESKS_H
