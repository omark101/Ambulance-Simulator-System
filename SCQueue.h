#ifndef SCQUEUE_H
#define SCQUEUE_H

#include "Car.h"

class SCQueue {
private:
    Car* front;
    Car* rear;
    int SCID;

public:
    SCQueue();
    ~SCQueue();

    bool isEmpty() const;
    void enqueue(int hospitalID);
    Car* dequeue();
    Car* peek() const;
    Car* dequeueFromHospital(int hid);
};

#endif // SCQUEUE_H
