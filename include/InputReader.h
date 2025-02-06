#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>

class InputReader {
public:
    struct Request {
        std::string type;
        int qt;
        int pid;
        int hid;
        int dst;
        int svr;
    };

    struct Cancellation {
        int time;
        int pid;
        int hid;
    };

private:
    int numHospitals;
    double speedSCars;
    double speedNCars;
    double** distanceMatrix;
    int* sCars;
    int* nCars;
    Request* requests;
    int numRequests;
    Cancellation* cancellations;
    int numCancellations;

public:
    InputReader();
    ~InputReader();

    bool readFile(const std::string& filename);
    int getNumHospitals() const;
    double getSpeedSCars() const;
    double getSpeedNCars() const;
    double** getDistanceMatrix() const;
    int* getSCars() const;
    int* getNCars() const;
    Request* getRequests() const;
    int getNumRequests() const;
    Cancellation* getCancellations() const;
    int getNumCancellations() const;

private:
    void parseRequest(const std::string& line, Request& req);
    void parseCancellation(const std::string& line, Cancellation& cancel);
};

#endif // INPUTREADER_H
