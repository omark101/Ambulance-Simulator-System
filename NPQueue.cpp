#include "NPQueue.h"

NPQueue::NPQueue() : front(nullptr), rear(nullptr), NPID(1) {}

NPQueue::~NPQueue() {
    while (!isEmpty()) {
        Patient* temp = dequeue();
        delete temp;
    }
}

bool NPQueue::isEmpty() const {
    return front == nullptr;
}

void NPQueue::enqueue(int timestamp, int pid, int hid, int dst) {
    Patient* newPatient = new Patient(pid, "Normal", timestamp, 0, hid, dst);
    if (isEmpty()) {
        front = rear = newPatient;
        return;
    }
    rear->next = newPatient;
    rear = newPatient;
}

Patient* NPQueue::dequeue() {
    if (isEmpty()) {
        return nullptr;
    }

    Patient* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    temp->next = nullptr;
    return temp;
}

Patient* NPQueue::peek() const {
    return front;
}

bool NPQueue::cancelPatient(int pid, int hid) {
    if (isEmpty()) return false;

    Patient* current = front;
    Patient* previous = nullptr;

    while (current != nullptr) {
        if (current->ID == pid && current->hid == hid) {
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
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}
