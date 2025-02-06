#include "SPQueue.h"

SPQueue::SPQueue() : front(nullptr), rear(nullptr), SPID(1) {}

SPQueue::~SPQueue() {
    while (!isEmpty()) {
        Patient* temp = dequeue();
        delete temp;
    }
}

bool SPQueue::isEmpty() const {
    return front == nullptr;
}

void SPQueue::enqueue(int timestamp, int pid, int hid, int dst) {
    Patient* newPatient = new Patient(pid, "Special", timestamp, 0, hid, dst);
    if (isEmpty()) {
        front = rear = newPatient;
        return;
    }
    rear->next = newPatient;
    rear = newPatient;
}

Patient* SPQueue::dequeue() {
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

Patient* SPQueue::peek() const {
    return front;
}

bool SPQueue::hasPatient(int pid, int hid) const {
    Patient* current = front;
    while (current != nullptr) {
        if (current->ID == pid && current->hid == hid) {
            return true;
        }
        current = current->next;
    }
    return false;
}
