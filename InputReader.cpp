#include "InputReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

InputReader::InputReader()
    : numHospitals(0), speedSCars(0.0), speedNCars(0.0),
      distanceMatrix(nullptr), sCars(nullptr), nCars(nullptr),
      requests(nullptr), numRequests(0), cancellations(nullptr),
      numCancellations(0) {}

InputReader::~InputReader() {
    if (distanceMatrix) {
        for (int i = 0; i < numHospitals; ++i) {
            delete[] distanceMatrix[i];
        }
        delete[] distanceMatrix;
    }
    delete[] sCars;
    delete[] nCars;
    delete[] requests;
    delete[] cancellations;
}

bool InputReader::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    // Number of hospitals
    while (getline(file, line) && line.empty());
    numHospitals = std::stoi(line);

    // Car speeds
    while (getline(file, line) && line.empty());
    std::istringstream speedStream(line);
    speedStream >> speedSCars >> speedNCars;

    // Distance matrix
    distanceMatrix = new double*[numHospitals];
    for (int i = 0; i < numHospitals; ++i) {
        distanceMatrix[i] = new double[numHospitals];
        while (getline(file, line) && line.empty());
        std::istringstream distStream(line);
        for (int j = 0; j < numHospitals; ++j) {
            distStream >> distanceMatrix[i][j];
        }
    }

    // Cars per hospital
    sCars = new int[numHospitals];
    nCars = new int[numHospitals];
    for (int i = 0; i < numHospitals; ++i) {
        while (getline(file, line) && line.empty());
        std::istringstream carStream(line);
        carStream >> sCars[i] >> nCars[i];
    }

    // Number of requests
    while (getline(file, line) && line.empty());
    numRequests = std::stoi(line);

    requests = new Request[numRequests];
    for (int i = 0; i < numRequests; ++i) {
        while (getline(file, line) && line.empty());
        parseRequest(line, requests[i]);
    }

    // Number of cancellations
    while (getline(file, line) && line.empty());
    numCancellations = std::stoi(line);

    cancellations = new Cancellation[numCancellations];
    for (int i = 0; i < numCancellations; ++i) {
        while (getline(file, line) && line.empty());
        parseCancellation(line, cancellations[i]);
    }

    return true;
}

void InputReader::parseRequest(const std::string& line, Request& req) {
    std::istringstream reqStream(line);
    reqStream >> req.type >> req.qt >> req.pid >> req.hid >> req.dst;
    req.svr = 0;
    if (req.type == "EP") {
        reqStream >> req.svr;
    }
}

void InputReader::parseCancellation(const std::string& line, Cancellation& cancel) {
    std::istringstream cancelStream(line);
    cancelStream >> cancel.time >> cancel.pid >> cancel.hid;
}

int InputReader::getNumHospitals() const {
    return numHospitals;
}

double InputReader::getSpeedSCars() const {
    return speedSCars;
}

double InputReader::getSpeedNCars() const {
    return speedNCars;
}

double** InputReader::getDistanceMatrix() const {
    return distanceMatrix;
}

int* InputReader::getSCars() const {
    return sCars;
}

int* InputReader::getNCars() const {
    return nCars;
}

InputReader::Request* InputReader::getRequests() const {
    return requests;
}

int InputReader::getNumRequests() const {
    return numRequests;
}

InputReader::Cancellation* InputReader::getCancellations() const {
    return cancellations;
}

int InputReader::getNumCancellations() const {
    return numCancellations;
}
