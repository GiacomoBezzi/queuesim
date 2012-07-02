#include "../include/queue.h"

queue::queue() {
    length = 0;
    max_length = 0;
}

queue::~queue() {
    thequeue.clear();
}

void queue::add_agent(agent theagent) {
    thequeue.push_back(theagent);
    length += 1;
    if (length > max_length) max_length = length;
}

agent queue::get_next() {
    agent next = thequeue.front();
    thequeue.pop_front();
    length -= 1;
    return next;
}

bool queue::is_empty() {
    return thequeue.empty();
}

int queue::get_length() {
    return length;
}

int queue::get_maxlength() {
    return max_length;
}
