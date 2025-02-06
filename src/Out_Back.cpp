#include "Out_Back.h"
#include "NCQueue.h"
#include "SCQueue.h"

Out_Back::OutCarNode::OutCarNode(int rTime, Car* c)
    : returnTime(rTime), car(c), next(nullptr) {}

Out_Back::Out_Back()
    : outCarsFront(nullptr), outCarsRear(nullptr),
      finishedPatientsFront(nullptr), finishedPatientsRear(nullptr) {}

Out_Back::~Out_Back() {
    while (outCarsFront) {
        OutCarNode* temp = outCarsFront;
        outCarsFront = outCarsFront->next;
        delete temp->car;
        delete temp;
    }
    while (finishedPatientsFront) {
        Patient* temp = finishedPatientsFront;
        finishedPatientsFront = finishedPatientsFront->next;
        delete temp;
    }
}

bool Out_Back::hasActiveCars() const {
    return outCarsFront != nullptr;
}

void Out_Back::addOutCar(int returnTime, Car* car) {
    OutCarNode* newNode = new OutCarNode(returnTime, car);
    if (!outCarsFront || returnTime < outCarsFront->returnTime) {
        newNode->next = outCarsFront;
        outCarsFront = newNode;
        if (!outCarsRear) {
            outCarsRear = newNode;
        }
        return;
    }

    OutCarNode* current = outCarsFront;
    while (current->next && current->next->returnTime <= returnTime) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    if (!newNode->next) {
        outCarsRear = newNode;
    }
}

void Out_Back::addFinishedPatient(Patient* patient) {
    if (!finishedPatientsFront) {
        finishedPatientsFront = finishedPatientsRear = patient;
    } else {
        finishedPatientsRear->next = patient;
        finishedPatientsRear = patient;
    }
}

void Out_Back::processReturnedCars(int currentTime, NCQueue& ncQueue, SCQueue& scQueue) {
    while (outCarsFront && outCarsFront->returnTime <= currentTime) {
        OutCarNode* temp = outCarsFront;
        outCarsFront = outCarsFront->next;
        if (!outCarsFront) {
            outCarsRear = nullptr;
        }

        if (temp->car->Type == "Normal") {
            ncQueue.enqueue(temp->car->HospitalID);
        } else if (temp->car->Type == "Special") {
            scQueue.enqueue(temp->car->HospitalID);
        }
        delete temp->car;
        delete temp;
    }
}

Patient* Out_Back::getNextFinishedPatient() {
    if (!finishedPatientsFront) return nullptr;
    Patient* patient = finishedPatientsFront;
    finishedPatientsFront = finishedPatientsFront->next;
    if (!finishedPatientsFront) {
        finishedPatientsRear = nullptr;
    }
    patient->next = nullptr;
    return patient;
}
