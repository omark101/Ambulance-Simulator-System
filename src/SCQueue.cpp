#include "SCQueue.h"

SCQueue::SCQueue() : front(nullptr), rear(nullptr), SCID(1) {}

SCQueue::~SCQueue() {
    while (!isEmpty()) {
        Car* temp = dequeue();
        delete temp;
    }
}

bool SCQueue::isEmpty() const {
    return front == nullptr;
}

void SCQueue::enqueue(int hospitalID) {
    Car* newCar = new Car(SCID++, "Special", hospitalID);
    if (isEmpty()) {
        front = rear = newCar;
        return;
    }
    rear->next = newCar;
    rear = newCar;
}

Car* SCQueue::dequeue() {
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

Car* SCQueue::peek() const {
    return front;
}

Car* SCQueue::dequeueFromHospital(int hid) {
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
