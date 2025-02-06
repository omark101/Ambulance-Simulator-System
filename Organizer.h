#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "EPQueue.h"
#include "NPQueue.h"
#include "SPQueue.h"
#include "NCQueue.h"
#include "SCQueue.h"
#include "Out_Back.h"
#include "Hospital.h"
#include "InputReader.h"

class Organizer {
private:
    struct OutputRecord {
        int finishTime;
        int patientID;
        int queueTime;
        int waitTime;
        OutputRecord* next;

        OutputRecord(int ft, int pid, int qt, int wt);
    };

    struct Statistics {
        int totalPatients;
        int npCount;
        int spCount;
        int epCount;
        int totalCars;
        int scCount;
        int ncCount;
        int totalWaitTime;
        int epNotServedByHome;
        int totalBusyTime;
        int simulationTime;

        Statistics();
    };

    EPQueue epQueue;
    NPQueue npQueue;
    SPQueue spQueue;
    NCQueue ncQueue;
    SCQueue scQueue;
    Out_Back outBack;
    Hospital hospital;

    int currentTimestamp;
    double speedSCars;
    double speedNCars;
    int numHospitals;

    OutputRecord* recordsHead;
    Statistics stats;
    bool isInteractiveMode;

public:
    Organizer();
    ~Organizer();

    void setMode(bool interactive);
    void initialize(InputReader& input);
    void handleRequest(const InputReader::Request& req);
    void handleCancellation(const InputReader::Cancellation& cancel);
    void servePatient();
    void processReturnedCars();
    void advanceTime();
    int getCurrentTimestamp() const;
    bool isSimulationComplete() const;
    void generateOutputFile(const std::string& filename);

private:
    Car* assignCarToEP(Patient* patient);
    int findBestHospitalForEP(Patient* patient);
    void transportPatient(Patient* patient, Car* car);
    void addOutputRecord(int ft, int pid, int qt, int wt);
};

#endif // ORGANIZER_H
