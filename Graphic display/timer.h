/*********************************************************************************
 * File: timer.h
 * Author: Sean Elia
 * 
 * A struct to help keep track of the time spent calculating the next board state
*********************************************************************************/
#ifndef TIMER_H_483
#define TIMER_H_483

struct timer {
    // these member variables can be accessed directly,
    // but they should not be updated directly
    double total, min, max;
    int count;

    // constructor - initailizes variables
    timer() {
        this->total = 0;
        this->count = 0;
        this->min = -1; // dummy value to indicate no times recorded yet
        this->max = -1; // dummy value to indicate no times recorded yet
    }

    // adds the passed vale to total, increments count, and updates min and max as needed
    void addTime(double time) {
        total += time;
        count ++;
        if (min < 0 || time < min) {
            min = time;
        }
        if (max < 0 || time > max) {
            max = time;
        }
    }

    // returns the average time to complete a step
    double avg() {
        if (count > 0) {
            return total / count;
        } else {
            return -1;
        }
    }
};

#endif