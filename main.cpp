/****************************************
This program runs a simple simulation on a queue

author: Giacomo Bezzi
date: 2012-04-15

TODO:
1. Save all results e.g., wait times, queue times
2. Know which desk is being selected
3. Read from command args
4. Make a GUI **
****************************************/

#include <iostream>
#include <time.h>
#include <math.h>

#include "include/agent.h"
#include "include/queue.h"
#include "include/all_desks.h"
#include "include/arrivals.h"

using namespace std;

int main() {

    /** TODO: these must be read from args */
    /***********************************/
    time_t seed;
    time(&seed);
    double mean = 60*5;   // mean service time
    double sd = 4;      // standard deviation of service time
    double lambda = 60; // mean inter-arrival time
    double sd_arr = 10;
    int n_desks = 5;
    double max_time = 2*60*60;
    /***********************************/

    /** paramaters */
    /***********************************/
    double total_wait = 0;
    int total_agents = 0;
    list<double> wait_times;
    double max_wait = 0;
    /***********************************/

    /** create objects */
    /***********************************/
    queue thequeue;

    arrivals arrival_list;
    arrival_list.set_param(lambda, sd_arr, mean, sd);
    arrival_list.set_seed(seed*321+231);
    arrival_list.gen_list(max_time);

    total_agents = arrival_list.get_length();

    all_desks thedesks;
    thedesks.set(n_desks);
    /***********************************/

    /** loop until we are finished */
    /***********************************/
    double curr_time = 0;

    while((arrival_list.get_length() > 0) | (thequeue.get_length() > 0)) {

        if(thequeue.is_empty()) {
            curr_time = arrival_list.get_next_time();
            agent newagent = arrival_list.get_next();

            if(thedesks.is_free(curr_time)) {
                double finish_time = newagent.go(curr_time);
                if(! thedesks.launch(finish_time, curr_time)) exit(1);
                total_wait += newagent.get_wait_time();
                wait_times.push_back(newagent.get_wait_time());
                if(newagent.get_wait_time() > max_wait) max_wait = newagent.get_wait_time();
            }
            else { // no free desks
                thequeue.add_agent(newagent);
            }
        }
        else { // existing queue
            if(arrival_list.get_length() > 0) { // someone still to come?
                if(arrival_list.get_next_time() < thedesks.get_first_free()) { // arrival happens first
                    curr_time = arrival_list.get_next_time();
                    agent newagent = arrival_list.get_next();
                    thequeue.add_agent(newagent);
                }
                else { // desk free happens first
                    curr_time = thedesks.get_first_free();
                    agent newagent = thequeue.get_next();
                    double finish_time = newagent.go(curr_time);
                    if(! thedesks.launch(finish_time, curr_time)) exit(2);
                    total_wait += newagent.get_wait_time();
                    wait_times.push_back(newagent.get_wait_time());
                    if(newagent.get_wait_time() > max_wait) max_wait = newagent.get_wait_time();
                }
            }

            else { // just queue
                curr_time = thedesks.get_first_free();
                agent newagent = thequeue.get_next();
                double finish_time = newagent.go(curr_time);
                if(! thedesks.launch(finish_time, curr_time)) exit(2);
                total_wait += newagent.get_wait_time();
                wait_times.push_back(newagent.get_wait_time());
                if(newagent.get_wait_time() > max_wait) max_wait = newagent.get_wait_time();
            }
        }
    }
    /***********************************/

    cout << "          SIMULATION TERMINATED\n";
    cout << "***********************************************\nSummary:\n\n";

    cout << "# of customers served:    " << total_agents << "\n";

    double h = floor(total_wait/total_agents/3600);
    double m = floor(total_wait/total_agents/60) - h*60;
    double s = round(total_wait/total_agents) -h*3600 - m*60;

    cout << "Average wait time:        " << h <<"h " << m << "m " << s << "s\n";

    h = floor(max_wait/3600);
    m = floor(max_wait/60) - h*60;
    s = round(max_wait) -h*3600 - m*60;

    cout << "Max wait time:            "<< h <<"h " << m << "m " << s << "s\n";
    cout << "Max queue length:         " << thequeue.get_maxlength() << "\n";

    h = floor(curr_time/3600);
    m = floor(curr_time/60) - h*60;
    s = round(curr_time) -h*3600 - m*60;

    cout << "Finish time:              " << h <<"h " << m << "m " << s << "s\n";
    cout << "***********************************************\n\n";

    /** Make a histogram */
    /***********************************/
if(max_wait > 0) {

    int hist_size = 15;
    if(hist_size > thequeue.get_maxlength()) hist_size = thequeue.get_maxlength();
    int hist_height = 15;
    double step = max_wait/hist_size;
    double hist[hist_size];
    double levels[hist_size];
    int max = 1;

    for(int i=0; i<hist_size; i++) {
        levels[i] = step*(hist_size-i);
        //cout << levels[i] << " ; ";
        hist[i] = 0;
    }

    for (list<double>::iterator it = wait_times.begin(); it != wait_times.end(); it++) {
        for(int i=0; i<hist_size; i++) {
            if(*it>=levels[i]) {
                hist[i] += 1;
                if(hist[i] > max) max = hist[i];
                break;
            }
        }
    }
    //cout << "\n\n";
    for (int i=0; i<hist_size; i++) {
        hist[i] = hist[i]/max*hist_height;
        //cout << hist[i] << " ; ";
    }

    cout << "\n\n";
     cout << "         HISTOGRAM OF WAITING TIMES\n";
    cout << "***********************************************\n";

    int curr_height = hist_height;

    cout << "^\n|\n";
    while (curr_height>=0) {
        cout << "|";
        for (int i=0; i<hist_size; i++) {
            if(curr_height > 0) {
                if(hist[i] >= curr_height) cout << "  #  ";
                else cout << "     ";
            }
            else {
                int number = round(levels[i]/60);
                if(number >= 100) cout << "  " << number << "";
                else if(number >= 10) cout << "  " << number << " ";
                else cout << "  " << number << "  ";
            }
        }
        cout << "\n";
        curr_height -= 1;
    }
}
    /***********************************/
/*
    cout << "Arrival times: ";
    list<double> arrival_times = arrival_list.get_times();
    for (list<double>::iterator it = arrival_times.begin(); it != arrival_times.end(); it++) {
        cout << *it << " ; ";
    }
    cout << "\n";
*/
    return 0;
}
