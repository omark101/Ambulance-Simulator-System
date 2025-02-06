#ifndef NPQUEUE_H
#define NPQUEUE_H

#include "Patient.h"

class NPQueue {
private:
    Patient* front;
    Patient* rear;
    int NPID;

public:
    NPQueue();
    ~NPQueue();

    bool isEmpty() const;
    void enqueue(int timestamp, int pid, int hid, int dst);
    Patient* dequeue();
    Patient* peek() const;
    bool cancelPatient(int pid, int hid);
};

#endif // NPQUEUE_H
