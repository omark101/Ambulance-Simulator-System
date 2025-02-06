#include "Patient.h"

Patient::Patient(int id, const std::string& s, int timestamp, int p, int hospitalID, int distance)
    : ID(id), priority(p), severity(s), timeStamp(timestamp), hid(hospitalID), dst(distance), next(nullptr) {}
