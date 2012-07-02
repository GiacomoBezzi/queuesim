#include "../include/rexp.h"

rexp::rexp() {
    lambda = 0;
    sd = 0;
    myseed = 1;
}

rexp::~rexp() {
    //dtor
}

void rexp::set_mean(double mean, double sigma) {
    if(mean < 0) exit(1);
    else {
        lambda = mean;
        sd = sigma;
    }
}

void rexp::set_seed(int theseed) {
    myseed = theseed;
}

double rexp::get_exp() {
    boost::mt19937 gener(1);
    boost::normal_distribution<> normal(lambda, sd);
    boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > rng(gener, normal);

    rng.engine().seed(myseed);

    return rng();
}
