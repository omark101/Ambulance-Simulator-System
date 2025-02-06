#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
public:
    int ID;
    int priority;
    std::string severity;
    int timeStamp;
    int hid;
    int dst;
    Patient* next;

    Patient(int id, const std::string& s, int timestamp, int p = 0, int hospitalID = 1, int distance = 0);
};

#endif // PATIENT_H
