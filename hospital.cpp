#include <bits/stdc++.h>
using namespace std;

struct Patient {
    string name;
    bool emergency;   
    int severity;     
    int arrivalOrder; 
};
struct CompareEmergency {
    bool operator()(const Patient& a, const Patient& b) {
        if (a.severity == b.severity)
            return a.arrivalOrder > b.arrivalOrder; 
        return a.severity < b.severity; 
    }
};

class HospitalQueue {
private:
    priority_queue<Patient, vector<Patient>, CompareEmergency> emergencyQueue;
    queue<Patient> regularQueue;
    int arrivalCounter = 0;
    const int consultTime = 10; 

public:
    void addPatient(string name, bool emergency, int severity = 0) {
        Patient p{name, emergency, severity, arrivalCounter++};
        if (emergency)
            emergencyQueue.push(p);
        else
            regularQueue.push(p);

        cout << "Patient " << name << " added to "
             << (emergency ? "Emergency Queue." : "Regular Queue.") << endl;
    }

    void serveNextPatient() {
        if (!emergencyQueue.empty()) {
            Patient p = emergencyQueue.top();
            emergencyQueue.pop();
            cout << "Serving EMERGENCY patient: " << p.name
                 << " (Severity " << p.severity << ")\n";
        } else if (!regularQueue.empty()) {
            Patient p = regularQueue.front();
            regularQueue.pop();
            cout << "Serving REGULAR patient: " << p.name << endl;
        } else {
            cout << "No patients in queue.\n";
        }
    }

    void showWaitTimes() {
        cout << "\n=== Estimated Wait Times ===\n";
        int timeElapsed = 0;
        auto emCopy = emergencyQueue; 
        while (!emCopy.empty()) {
            Patient p = emCopy.top();
            emCopy.pop();
            cout << p.name << " (EMERGENCY, Severity " << p.severity 
                 << ") → Wait: " << timeElapsed << " mins\n";
            timeElapsed += consultTime;
        }
        auto regCopy = regularQueue; 
        while (!regCopy.empty()) {
            Patient p = regCopy.front();
            regCopy.pop();
            cout << p.name << " (REGULAR) → Wait: " << timeElapsed << " mins\n";
            timeElapsed += consultTime;
        }

        if (timeElapsed == 0) 
            cout << "No patients waiting.\n";
    }
};

int main() {
    HospitalQueue hospital;
    int choice, severity;
    string name;

    while (true) {
        cout << "\n=== Hospital Queue System ===\n";
        cout << "1. Add Regular Patient\n";
        cout << "2. Add Emergency Patient\n";
        cout << "3. Serve Next Patient\n";
        cout << "4. Show Wait Times\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Patient Name: ";
                cin >> name;
                hospital.addPatient(name, false);
                break;
            case 2:
                cout << "Enter Patient Name: ";
                cin >> name;
                cout << "Enter Severity (1-10, higher = more critical): ";
                cin >> severity;
                hospital.addPatient(name, true, severity);
                break;
            case 3:
                hospital.serveNextPatient();
                break;
            case 4:
                hospital.showWaitTimes();
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
