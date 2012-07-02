#ifndef AGENT_H
#define AGENT_H


class agent {
    double service_time;
    double arrival_time;
    double leave_time;
    double queue_start;
    double queue_end;
    double queue_time;
    double mean;
    double sd;
    public:
    agent();
    ~agent();
    void set_param(double mu, double sigma2);
    void set(double arrival, int theseed);
    double go(double go_start);
    double get_total_time();
    double get_wait_time();
    double get_arrival_time();
};

#endif // AGENT_H
