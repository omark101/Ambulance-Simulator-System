#include <iostream>
#include <limits>
#include <conio.h>
#include <windows.h>
#include "InputReader.h"
#include "Organizer.h"

int main() {
    std::cout << "Select simulation mode:" << std::endl;
    std::cout << "1. Interactive Mode" << std::endl;
    std::cout << "2. Silent Mode" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";

    int modeChoice;
    std::cin >> modeChoice;
    bool isInteractive = (modeChoice == 1);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    InputReader inputReader;
    std::string inputFileName;
    std::cout << "Enter the input file path: ";
    std::getline(std::cin, inputFileName);

    if (!inputReader.readFile(inputFileName)) {
        std::cerr << "Failed to read input file. Exiting." << std::endl;
        return 1;
    }

    Organizer organizer;
    organizer.setMode(isInteractive);
    organizer.initialize(inputReader);

    auto requests = inputReader.getRequests();
    int numRequests = inputReader.getNumRequests();
    auto cancellations = inputReader.getCancellations();
    int numCancellations = inputReader.getNumCancellations();

    int currentRequestIndex = 0;
    int currentCancellationIndex = 0;

    if (isInteractive) {
        std::cout << "\nInteractive Mode Started" << std::endl;
        std::cout << "Press 'N' to advance to the next timestep" << std::endl;
        std::cout << "Press 'Q' to quit simulation" << std::endl;

        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'n' || key == 'N') {
                    int currentTime = organizer.getCurrentTimestamp();

                    while (currentRequestIndex < numRequests &&
                           requests[currentRequestIndex].qt == currentTime) {
                        organizer.handleRequest(requests[currentRequestIndex]);
                        currentRequestIndex++;
                    }

                    while (currentCancellationIndex < numCancellations &&
                           cancellations[currentCancellationIndex].time == currentTime) {
                        organizer.handleCancellation(cancellations[currentCancellationIndex]);
                        currentCancellationIndex++;
                    }

                    organizer.servePatient();
                    organizer.processReturnedCars();
                    organizer.advanceTime();

                    std::cout << "\nTimestep " << currentTime << " completed" << std::endl;
                } else if (key == 'q' || key == 'Q') {
                    break;
                }
            }
        }
    } else {
        std::cout << "Silent Mode: Processing..." << std::endl;

        while (currentRequestIndex < numRequests ||
               currentCancellationIndex < numCancellations ||
               !organizer.isSimulationComplete()) {

            int currentTime = organizer.getCurrentTimestamp();

            while (currentRequestIndex < numRequests &&
                   requests[currentRequestIndex].qt == currentTime) {
                organizer.handleRequest(requests[currentRequestIndex]);
                currentRequestIndex++;
            }

            while (currentCancellationIndex < numCancellations &&
                   cancellations[currentCancellationIndex].time == currentTime) {
                organizer.handleCancellation(cancellations[currentCancellationIndex]);
                currentCancellationIndex++;
            }

            organizer.servePatient();
            organizer.processReturnedCars();
            organizer.advanceTime();
        }
    }

    std::string outputFileName;
    std::cout << "Enter the output file name: ";
    std::getline(std::cin, outputFileName);

    organizer.generateOutputFile(outputFileName);
    std::cout << "Simulation completed. Output file created: " << outputFileName << std::endl;

    return 0;
}
