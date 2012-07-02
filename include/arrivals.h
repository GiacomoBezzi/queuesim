#ifndef ARRIVALS_H
#define ARRIVALS_H

#include <list>

#include "rexp.h"
#include "agent.h"

class arrivals
{
    public:
        arrivals();
        virtual ~arrivals();
        void set_param(double arrivals_mu, double arrivals_sigma, double agent_mu, double agent_sigma);
        void set_seed(int theseed);
        void gen_list(double max_time);
        double get_next_time();
        agent get_next();
        int get_length();
        std::list<double> get_times();
    protected:
    private:
    std::list<agent> agents;
    double mean_arrivals;
    double sd_arrivals;
    double mean_agent;
    double sd_agent;
    int myseed;
    int length;
    std::list<double> times_arrivals;
};

#endif // ARRIVALS_H
