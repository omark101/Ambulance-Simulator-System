#ifndef OUT_BACK_H
#define OUT_BACK_H

#include "Car.h"
#include "Patient.h"

class NCQueue;
class SCQueue;

class Out_Back {
private:
    struct OutCarNode {
        int returnTime;
        Car* car;
        OutCarNode* next;

        OutCarNode(int rTime, Car* c);
    };

    OutCarNode* outCarsFront;
    OutCarNode* outCarsRear;
    Patient* finishedPatientsFront;
    Patient* finishedPatientsRear;

public:
    Out_Back();
    ~Out_Back();

    bool hasActiveCars() const;
    void addOutCar(int returnTime, Car* car);
    void addFinishedPatient(Patient* patient);
    void processReturnedCars(int currentTime, NCQueue& ncQueue, SCQueue& scQueue);
    Patient* getNextFinishedPatient();
};

#endif // OUT_BACK_H
