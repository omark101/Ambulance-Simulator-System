#ifndef EPQUEUE_H
#define EPQUEUE_H

#include "Patient.h"

class EPQueue {
private:
    Patient* front;
    Patient* rear;
    int EPID;

public:
    EPQueue();
    ~EPQueue();

    bool isEmpty() const;
    void enqueue(int svr, int timestamp, int pid, int hid, int dst);
    Patient* dequeue();
    Patient* peek() const;
    bool hasPatient(int pid, int hid) const;
    int getQueueLength(int hid) const;
};

#endif // EPQUEUE_H
