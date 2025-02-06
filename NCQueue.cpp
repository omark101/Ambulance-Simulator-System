#include "NCQueue.h"

NCQueue::NCQueue() : front(nullptr), rear(nullptr), NCID(1) {}

NCQueue::~NCQueue() {
    while (!isEmpty()) {
        Car* temp = dequeue();
        delete temp;
    }
}

bool NCQueue::isEmpty() const {
    return front == nullptr;
}

void NCQueue::enqueue(int hospitalID) {
    Car* newCar = new Car(NCID++, "Normal", hospitalID);
    if (isEmpty()) {
        front = rear = newCar;
        return;
    }
    rear->next = newCar;
    rear = newCar;
}

Car* NCQueue::dequeue() {
    if (isEmpty()) {
        return nullptr;
    }

    Car* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    temp->next = nullptr;
    return temp;
}

Car* NCQueue::peek() const {
    return front;
}

Car* NCQueue::dequeueFromHospital(int hid) {
    if (isEmpty()) {
        return nullptr;
    }

    Car* current = front;
    Car* previous = nullptr;

    while (current != nullptr) {
        if (current->HospitalID == hid) {
            if (previous == nullptr) {
                front = current->next;
                if (front == nullptr) {
                    rear = nullptr;
                }
            } else {
                previous->next = current->next;
                if (current->next == nullptr) {
                    rear = previous;
                }
            }
            current->next = nullptr;
            return current;
        }
        previous = current;
        current = current->next;
    }

    return nullptr;
}
