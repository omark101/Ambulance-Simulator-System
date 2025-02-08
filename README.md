# 🏩 Ambulance Simulator System

## 📌 Project Overview  
The **Ambulance Simulator System** is a robust C++ simulation designed to manage and optimize emergency patient transportation across a network of hospitals. It handles patient prioritization, ambulance allocation, and hospital capacity tracking to ensure efficient emergency response.

---

## ✨ Key Features  

### 🚦 Intelligent Queue Management  
- **Priority-based queues**:  
  - **Emergency Patients (EP)**: Highest priority (sorted by severity).  
  - **Special Patients (SP)**: Require specialized ambulances.  
  - **Normal Patients (NP)**: First-come, first-served.  

### 🚗 Dynamic Ambulance Allocation  
- Assigns **Normal (NC)** and **Special (SC)** ambulances based on:  
  - Hospital proximity.  
  - Patient urgency.  
  - Resource availability.  

### 🏥 Multi-Hospital Network  
- **Distance matrix** for realistic routing.  
- Load balancing across hospitals.  

### ⚙️ Simulation Modes  
- **Interactive Mode**: Step-by-step execution.  
- **Silent Mode**: Automated for performance testing.  

### 📊 Performance Metrics  
- Average waiting times.  
- Ambulance utilization rates.  
- Hospital efficiency stats.  
- Detailed event logs on each timestep.  

---

## ⚠ Error Handling & Edge Cases  
- **No available ambulances in the requested hospital**: two options.
  - Patients remain queued until an ambulance is free.
  - if EP (Patient rerouted to the nearest hospital).  
- **Simultaneous emergencies**: Prioritization is based on severity and arrival time.
- **Invalid input**: The system outputs error messages and ignores malformed data. 
---

## 🧐 Installation & Execution  

### 🗏 Prerequisites  
- C++ compiler (GCC, Clang, or MSVC).  
- CMake (≥3.10).  

### 🏢 Build Instructions  
```bash
git clone https://github.com/omark101/Ambulance-Simulator-System.git
cd Ambulance-Simulator-System
mkdir build && cd build
cmake .. && make
```

### 🚀 Run the Simulation
```bash
./Ambulance Simulator System
# Follow prompts to provide input file
```

## 📂 Input File Format Example  
```plaintext
4      # number of hospitals in the system  
110 75 # Speed of the cars repsectivly NC,SP /meter per timestep

0   154   587   634          
154   0   533   214      # Distnace matrix for hospitals N x N
587   533   0   945
634   214   945   0

5   11      # 3 SC , 11 NC in Hospital 1 (first row is hospital no.1)
2   2       # 2 SC , 2 NC in Hospital 2 (second row is hospital no.2)
6   15      # 6 SC , 15 NC in Hospital 3 (third row is hospital no.3)
1   2       # 1 SC , 2 NC in Hospital 4 (fourth row is hospital no.4)

150           # number of requests (this line should be followed with 5 requests) 

NP   3   1   2   159        
SP   3   2   1   588
EP   12  3   4   433   5
EP   8   4   3   220   3
SP   9   5   2   190
```
![image](https://github.com/user-attachments/assets/e6f6802d-1b08-4974-9a44-15b30bf49eab)

```
7

15   1   2
```
![image](https://github.com/user-attachments/assets/41f80bbc-b934-4b9f-84f4-86d7d31c4cd6)

---

### 📊 Formulas used  
![image](https://github.com/user-attachments/assets/b9d50a6a-14d5-412f-bd44-21338b248caf)

---

## 📊 Output  

### Simulation Results  
```Example
FT: 320, PID: 12, QT: 15, WT: 45
FT: 340, PID: 19, QT: 10, WT: 50
FT: 355, PID: 5,  QT: 20, WT: 60
```
```plain text
FT: <finish_time>, PID: <patient_id>, QT: <queue_time>, WT: <waiting_time>
```

---

### 🏥 Scenarios Explained
**Each input file in InputFiles/ represents a unique test case:**
- Scenario 1: Many users requesting the same hospital (high congestion).
- Scenario 2: Limited ambulances compared to demand (resource shortage).
- Scenario 3: Balanced patient distribution across hospitals.
- Scenario 4: Randomized patient requests and hospital availability.

---

### 📊 Statistics  
- **Total patients processed**  
- **Average waiting times**  
- **Ambulance utilization rates**  
- **Hospital resource efficiency**  
- **Event log tracking**  

---

## 🧬 Data Structures Used  
- **Priority Queues**: For EP patients (sorted by severity).  
- **Queues**: For SP/NP patient queues.  
- **Matrices**: Hospital distance storage.  
- **Linked Lists**: Efficient insertion/deletion for event processing.  

---

## 🗂 Project Structure  
```plaintext
src/
├── main.cpp                 # Simulation entry point
├── Patient.cpp              # Patient class implementation
├── Hospital.cpp             # Hospital resources/distance implementation
├── Car.cpp                  # Ambulance management implementation
├── EPQueue.cpp              # Emergency patient queue implementation
├── SPQueue.cpp              # Special patient queue implementation
├── NPQueue.cpp              # Normal patient queue implementation
├── Organizer.cpp            # Simulation logic implementation
├── InputReader.cpp          # Input parsing implementation
├── EventLogger.cpp          # Logs all events & statistics

include/
├── Patient.h                # Patient class interface
├── Hospital.h               # Hospital resources/distance interface
├── Car.h                    # Ambulance management interface
├── EPQueue.h                # Emergency patient queue interface
├── SPQueue.h                # Special patient queue interface
├── NPQueue.h                # Normal patient queue interface
├── Organizer.h              # Simulation logic interface
├── InputReader.h            # Input parsing interface
├── EventLogger.h            # Logging interface

InputFiles/
├── Scenario 1               # Input file Scenario (Many users requesting same hospital) 
├── Scenario 2               # Input file Scenario (Many users, fewer cars) 
├── Scenario 3               # Random sample 
└── Scenario 4               # Random sample
```

## 👥 Contributors  
- [Omer Ayman](https://github.com/omark101)  

---

## 📩 Contact  
- **Email**: [omerayman101@gmail.com](mailto:omerayman101@gmail.com)  
