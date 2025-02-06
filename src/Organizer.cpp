#include "Organizer.h"
#include <fstream>
#include <iostream>
#include <cmath>

Organizer::OutputRecord::OutputRecord(int ft, int pid, int qt, int wt)
    : finishTime(ft), patientID(pid), queueTime(qt), waitTime(wt), next(nullptr) {}

Organizer::Statistics::Statistics()
    : totalPatients(0), npCount(0), spCount(0), epCount(0),
      totalCars(0), scCount(0), ncCount(0), totalWaitTime(0),
      epNotServedByHome(0), totalBusyTime(0), simulationTime(0) {}

Organizer::Organizer()
    : currentTimestamp(0), speedSCars(0.0), speedNCars(0.0),
      numHospitals(0), recordsHead(nullptr), isInteractiveMode(true) {}

Organizer::~Organizer() {
    while (recordsHead) {
        OutputRecord* temp = recordsHead;
        recordsHead = recordsHead->next;
        delete temp;
    }
}

void Organizer::setMode(bool interactive) {
    isInteractiveMode = interactive;
}

void Organizer::initialize(InputReader& input) {
    numHospitals = input.getNumHospitals();
    speedSCars = input.getSpeedSCars();
    speedNCars = input.getSpeedNCars();

    hospital.initialize(numHospitals, input.getDistanceMatrix());

    for (int i = 0; i < numHospitals; ++i) {
        int hid = i + 1;
        for (int j = 0; j < input.getNCars()[i]; ++j) {
            ncQueue.enqueue(hid);
            stats.ncCount++;
        }
        for (int j = 0; j < input.getSCars()[i]; ++j) {
            scQueue.enqueue(hid);
            stats.scCount++;
        }
    }

    stats.totalCars = stats.ncCount + stats.scCount;
    currentTimestamp = 0;
}

void Organizer::handleRequest(const InputReader::Request& req) {
    if (req.type == "EP") {
        epQueue.enqueue(req.svr, req.qt, req.pid, req.hid, req.dst);
        stats.epCount++;
    } else if (req.type == "SP") {
        spQueue.enqueue(req.qt, req.pid, req.hid, req.dst);
        stats.spCount++;
    } else if (req.type == "NP") {
        npQueue.enqueue(req.qt, req.pid, req.hid, req.dst);
        stats.npCount++;
    }
    stats.totalPatients++;
}

void Organizer::handleCancellation(const InputReader::Cancellation& cancel) {
    if (npQueue.cancelPatient(cancel.pid, cancel.hid)) {
        stats.npCount--;
        stats.totalPatients--;
    }
}

void Organizer::servePatient() {
    while (true) {
        Patient* patient = nullptr;
        Car* car = nullptr;

        if (!epQueue.isEmpty()) {
            patient = epQueue.peek();
            car = assignCarToEP(patient);
            if (car) {
                patient = epQueue.dequeue();
                transportPatient(patient, car);
                continue;
            }
        }

        if (!spQueue.isEmpty() && (car = scQueue.dequeue())) {
            patient = spQueue.dequeue();
            transportPatient(patient, car);
            continue;
        }

        if (!npQueue.isEmpty() && (car = ncQueue.dequeue())) {
            patient = npQueue.dequeue();
            transportPatient(patient, car);
            continue;
        }

        break;
    }
}

void Organizer::processReturnedCars() {
    outBack.processReturnedCars(currentTimestamp, ncQueue, scQueue);
}

void Organizer::advanceTime() {
    currentTimestamp++;
    stats.simulationTime = currentTimestamp;
}

int Organizer::getCurrentTimestamp() const {
    return currentTimestamp;
}

bool Organizer::isSimulationComplete() const {
    return epQueue.isEmpty() && spQueue.isEmpty() && npQueue.isEmpty() && !outBack.hasActiveCars();
}

void Organizer::generateOutputFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }

    outFile << "Simulation Results:\n";
    outFile << "==================\n";

    for (OutputRecord* record = recordsHead; record; record = record->next) {
        outFile << "FT: " << record->finishTime
                << ", PID: " << record->patientID
                << ", QT: " << record->queueTime
                << ", WT: " << record->waitTime << "\n";
    }

    outFile << "\nSimulation Statistics:\n";
    outFile << "Total Patients: " << stats.totalPatients << "\n";
    outFile << "Normal Patients: " << stats.npCount << "\n";
    outFile << "Special Patients: " << stats.spCount << "\n";
    outFile << "Emergency Patients: " << stats.epCount << "\n";
    outFile.close();
}

Car* Organizer::assignCarToEP(Patient* patient) {
    Car* car = ncQueue.dequeue();
    if (!car) {
        car = scQueue.dequeue();
    }
    return car;
}

void Organizer::transportPatient(Patient* patient, Car* car) {
    double distance = hospital.getDistance(patient->hid, car->HospitalID);
    double speed = car->Type == "Normal" ? speedNCars : speedSCars;
    int travelTime = static_cast<int>(std::ceil(distance / speed));
    int finishTime = currentTimestamp + travelTime;

    addOutputRecord(finishTime, patient->ID, patient->timeStamp, finishTime - patient->timeStamp);

    outBack.addOutCar(finishTime, car);
    delete patient;
}

void Organizer::addOutputRecord(int ft, int pid, int qt, int wt) {
    OutputRecord* newRecord = new OutputRecord(ft, pid, qt, wt);
    if (!recordsHead || ft < recordsHead->finishTime) {
        newRecord->next = recordsHead;
        recordsHead = newRecord;
    } else {
        OutputRecord* current = recordsHead;
        while (current->next && current->next->finishTime <= ft) {
            current = current->next;
        }
        newRecord->next = current->next;
        current->next = newRecord;
    }
}
