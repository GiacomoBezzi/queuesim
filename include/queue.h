#ifndef QUEUE_H
#define QUEUE_H

#include "agent.h"
#include <list>

using namespace std;

class queue
{
    public:
        queue();
        virtual ~queue();
        void add_agent(agent theagent);
        agent get_next();
        bool is_empty();
        int get_length();
        int get_maxlength();
    protected:
    private:
        list<agent> thequeue;
        int length, max_length;
};

#endif // QUEUE_H
