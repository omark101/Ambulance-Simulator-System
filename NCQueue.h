#ifndef NCQUEUE_H
#define NCQUEUE_H

#include "Car.h"

class NCQueue {
private:
    Car* front;
    Car* rear;
    int NCID;

public:
    NCQueue();
    ~NCQueue();

    bool isEmpty() const;
    void enqueue(int hospitalID);
    Car* dequeue();
    Car* peek() const;
    Car* dequeueFromHospital(int hid);
};

#endif // NCQUEUE_H
