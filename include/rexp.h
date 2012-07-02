#ifndef REXP_H
#define REXP_H

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

class rexp
{
    public:
        rexp();
        void set_mean(double mean, double sigma);
        void set_seed(int theseed);
        double get_exp();
        virtual ~rexp();
    protected:
    private:
        double lambda;
        double sd;
        int myseed;
};

#endif // REXP_H
