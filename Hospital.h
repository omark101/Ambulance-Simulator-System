#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <iomanip>
#include <cmath>

struct HospitalInfo {
    int ID;
    double x;
    double y;

    HospitalInfo(int id = 1, double X = 0.0, double Y = 0.0);
};

class Hospital {
private:
    HospitalInfo* hospitals;
    double** distanceMatrix;
    int numHospitals;

public:
    Hospital();
    ~Hospital();

    void initialize(int num, double** distMatrix);
    void mapHospitals();
    void printHospitals() const;
    void printMatrix() const;
    double getDistance(int hid1, int hid2) const;
    int getNumHospitals() const;
    const HospitalInfo& getHospitalInfo(int hid) const;
};

#endif // HOSPITAL_H
