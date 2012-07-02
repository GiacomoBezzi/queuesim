#ifndef REGISTER_H
#define REGISTER_H

class register
{
    public:
        register();
        virtual ~register();
        void set(double how_long, double time_now);
        bool is_free(double time_now);
        double get_finish();
        int get_nclients();
    protected:
    private:
    double finish_time;
    int n_clients;
};

#endif // REGISTER_H
