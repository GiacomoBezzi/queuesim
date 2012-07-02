#ifndef DESK_H
#define DESK_H


class desk
{
    public:
        desk();
        virtual ~desk();
        void set(double finish);
        double get_finish();
        bool is_free(double time_now);
        int get_nclients();
    protected:
    private:
        double finish_time;
        int n_clients;
};

#endif // DESK_H
