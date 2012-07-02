#include "../include/agent.h"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

agent::agent() {
    arrival_time = 0;
    queue_start = 0;
    service_time = 0;
    leave_time = 0;
    queue_end = 0;
    queue_time = 0;
    mean = 30;    // in case you forget to set these
    sd = 8; //default param
}

agent::~agent()
{
    //dtor
}

void agent::set_param(double mu, double sigma) {
    mean = mu;
    sd = sigma;
}

void agent::set(double arrival, int theseed) {
    arrival_time = arrival;

    boost::mt19937 gener(1);
    boost::normal_distribution<> normal(mean, sd);
    boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > rng(gener, normal);

    rng.engine().seed(theseed);

    service_time = rng();
    queue_start = arrival;
}

double agent::go(double go_start) {
    queue_end = go_start;
    queue_time = queue_end - queue_start;
    leave_time = go_start + service_time;
    return leave_time;
}

double agent::get_total_time() {
    return queue_time + service_time;
}

double agent::get_wait_time() {
    return queue_time;
}

double agent::get_arrival_time() {
    return arrival_time;
}
