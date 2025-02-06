#include "EPQueue.h"

EPQueue::EPQueue() : front(nullptr), rear(nullptr), EPID(1) {}

EPQueue::~EPQueue() {
    while (!isEmpty()) {
        Patient* temp = dequeue();
        delete temp;
    }
}

bool EPQueue::isEmpty() const {
    return front == nullptr;
}

void EPQueue::enqueue(int svr, int timestamp, int pid, int hid, int dst) {
    Patient* newPatient = new Patient(pid, "Emergency", timestamp, svr, hid, dst);
    if (isEmpty()) {
        front = rear = newPatient;
        return;
    }

    if (svr < front->priority) {
        newPatient->next = front;
        front = newPatient;
        return;
    }

    Patient* temp = front;
    while (temp->next != nullptr && temp->next->priority <= svr) {
        temp = temp->next;
    }

    newPatient->next = temp->next;
    temp->next = newPatient;

    if (newPatient->next == nullptr) {
        rear = newPatient;
    }
}

Patient* EPQueue::dequeue() {
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

Patient* EPQueue::peek() const {
    return front;
}

bool EPQueue::hasPatient(int pid, int hid) const {
    Patient* current = front;
    while (current != nullptr) {
        if (current->ID == pid && current->hid == hid) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int EPQueue::getQueueLength(int hid) const {
    int count = 0;
    Patient* current = front;
    while (current != nullptr) {
        if (current->hid == hid) {
            count++;
        }
        current = current->next;
    }
    return count;
}
