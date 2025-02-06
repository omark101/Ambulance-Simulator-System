#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
public:
    int ID;
    std::string Type;
    int HospitalID;
    Car* next;

    Car(int id, const std::string& type, int hospitalID);
};

#endif // CAR_H
