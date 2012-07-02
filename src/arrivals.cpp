#include "../include/arrivals.h"

arrivals::arrivals() {
    mean_agent = 10; //default value
    sd_agent = 8;

    mean_arrivals = 10;

    length = 0;

    myseed = 1234;

}

arrivals::~arrivals() {
    agents.clear();
}

void arrivals::set_param(double arrivals_mu, double arrivals_sigma, double agent_mu, double agent_sigma) {
    mean_agent = agent_mu;
    sd_agent = agent_sigma;
    mean_arrivals = arrivals_mu;
    sd_arrivals = arrivals_sigma;
}

void arrivals::set_seed(int theseed) {
    myseed = theseed;
}

void arrivals::gen_list(double max_time) {

    rexp theclock;
    theclock.set_mean(mean_arrivals, sd_arrivals);
    theclock.set_seed(myseed);

    double curr_time = 0;

    agent newagent;
    newagent.set_param(mean_agent, sd_agent);

    while(curr_time < max_time) {

        curr_time += theclock.get_exp();
        if(curr_time < max_time) {
            newagent.set(curr_time, myseed+length);
            agents.push_back(newagent);
            times_arrivals.push_back(curr_time);
            length += 1;
        }
    }
}

double arrivals::get_next_time() {
    agent newagent = agents.front();
    return newagent.get_arrival_time();
}

agent arrivals::get_next() {
    agent newagent = agents.front();
    agents.pop_front();
    length -= 1;
    return newagent;
}

int arrivals::get_length() {
    return length;
}

std::list<double> arrivals::get_times() {
    return times_arrivals;
}
