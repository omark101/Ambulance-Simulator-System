#include "Hospital.h"
#include <iostream>
#include <iomanip>
#include <cmath>

HospitalInfo::HospitalInfo(int id, double X, double Y) : ID(id), x(X), y(Y) {}

Hospital::Hospital() : hospitals(nullptr), distanceMatrix(nullptr), numHospitals(0) {}

Hospital::~Hospital() {
    if (hospitals) {
        delete[] hospitals;
    }
    if (distanceMatrix) {
        for (int i = 0; i < numHospitals; ++i) {
            delete[] distanceMatrix[i];
        }
        delete[] distanceMatrix;
    }
}

void Hospital::initialize(int num, double** distMatrix) {
    numHospitals = num;
    hospitals = new HospitalInfo[numHospitals];
    for (int i = 0; i < numHospitals; ++i) {
        hospitals[i] = HospitalInfo(i + 1, 0.0, 0.0);
    }

    distanceMatrix = new double*[numHospitals];
    for (int i = 0; i < numHospitals; ++i) {
        distanceMatrix[i] = new double[numHospitals];
        for (int j = 0; j < numHospitals; ++j) {
            distanceMatrix[i][j] = distMatrix[i][j];
        }
    }

    mapHospitals();
}

void Hospital::mapHospitals() {
    for (int i = 0; i < numHospitals; ++i) {
        hospitals[i].x = i * 10.0;
        hospitals[i].y = 0.0;
    }

    for (int i = 0; i < numHospitals; ++i) {
        for (int j = i + 1; j < numHospitals; ++j) {
            if (distanceMatrix[i][j] > 0) {
                hospitals[j].y += distanceMatrix[i][j] / 1000.0;
            }
        }
    }
}

void Hospital::printHospitals() const {
    std::cout << "Hospitals and their Coordinates:" << std::endl;
    for (int i = 0; i < numHospitals; ++i) {
        std::cout << "Hospital ID: " << hospitals[i].ID
                  << ", Coordinates: (" << std::fixed << std::setprecision(2)
                  << hospitals[i].x << ", " << hospitals[i].y << ")" << std::endl;
    }
}

void Hospital::printMatrix() const {
    std::cout << "Distance Matrix:" << std::endl;
    for (int i = 0; i < numHospitals; ++i) {
        for (int j = 0; j < numHospitals; ++j) {
            std::cout << std::fixed << std::setprecision(2) << distanceMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

double Hospital::getDistance(int hid1, int hid2) const {
    if (hid1 < 1 || hid1 > numHospitals || hid2 < 1 || hid2 > numHospitals) {
        std::cerr << "Invalid Hospital ID(s) provided: " << hid1 << ", " << hid2 << std::endl;
        return -1.0;
    }
    return distanceMatrix[hid1 - 1][hid2 - 1];
}

int Hospital::getNumHospitals() const {
    return numHospitals;
}

const HospitalInfo& Hospital::getHospitalInfo(int hid) const {
    if (hid < 1 || hid > numHospitals) {
        std::cerr << "Invalid Hospital ID provided: " << hid << std::endl;
        return hospitals[0];
    }
    return hospitals[hid - 1];
}
