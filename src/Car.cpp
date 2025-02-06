#include "Car.h"

Car::Car(int id, const std::string& type, int hospitalID)
    : ID(id), Type(type), HospitalID(hospitalID), next(nullptr) {}
