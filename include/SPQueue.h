#ifndef SPQUEUE_H
#define SPQUEUE_H

#include "Patient.h"

class SPQueue {
private:
    Patient* front;
    Patient* rear;
    int SPID;

public:
    SPQueue();
    ~SPQueue();

    bool isEmpty() const;
    void enqueue(int timestamp, int pid, int hid, int dst);
    Patient* dequeue();
    Patient* peek() const;
    bool hasPatient(int pid, int hid) const;
};

#endif // SPQUEUE_H
