#include "../include/HospitalManagement.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// Constructor: initialize next IDs and load past data
HospitalManagement::HospitalManagement() {
    nextDoctorID = 101;
    nextPatientID = 201;
    nextAppointmentID = 301;

    loadDoctorsFromFile("doctors.txt");
    loadPatientsFromFile("patients.txt");
    loadAppointmentsFromFile("appointments.txt");
}

// ------------------- DOCTOR FUNCTIONS -------------------

void HospitalManagement::addDoctor() {
    Doctor d;
    cout << "\nAssigning Doctor ID: " << nextDoctorID << endl;
    d.inputInfo();

    // overwrite the ID to keep consistent numbering
    string data = d.toFileString();
    // format: 0|name|age|gender|spec|availability → replace 0 with nextDoctorID
    data = to_string(nextDoctorID) + data.substr(data.find('|'));

    Doctor finalDoctor;
    finalDoctor.fromFileString(data);

    doctors.push_back(finalDoctor);
    nextDoctorID++;

    saveDoctorsToFile("doctors.txt");
    cout << "\nDoctor added successfully!\n";
}

void HospitalManagement::listDoctors() const {
    if (doctors.empty()) {
        cout << "\nNo doctors available.\n";
        return;
    }
    displayList(doctors);   // TEMPLATE FUNCTION
}

void HospitalManagement::searchDoctorByID() const {
    cout << "\nEnter Doctor ID: ";
    int id;
    cin >> id;

    for (const auto& d : doctors) {
        if (d.getDoctorID() == id) {
            d.displayInfo();
            return;
        }
    }
    cout << "\nDoctor not found!\n";
}

// ------------------- PATIENT FUNCTIONS -------------------

void HospitalManagement::addPatient() {
    Patient p;
    cout << "\nAssigning Patient ID: " << nextPatientID << endl;
    p.inputInfo();

    // Replace ID inside toFileString
    string data = p.toFileString();
    data = to_string(nextPatientID) + data.substr(data.find('|'));

    Patient finalPatient;
    finalPatient.fromFileString(data);

    patients.push_back(finalPatient);
    nextPatientID++;

    savePatientsToFile("patients.txt");
    cout << "\nPatient added successfully!\n";
}

void HospitalManagement::listPatients() const {
    if (patients.empty()) {
        cout << "\nNo patients found.\n";
        return;
    }
    displayList(patients);   // TEMPLATE FUNCTION
}

void HospitalManagement::searchPatientByID() const {
    cout << "\nEnter Patient ID: ";
    int id;
    cin >> id;

    for (const auto& p : patients) {
        if (p.getPatientID() == id) {
            p.displayInfo();
            return;
        }
    }
    cout << "\nPatient not found!\n";
}

void HospitalManagement::assignDoctorToPatient() {
    cout << "\nEnter Patient ID: ";
    int pid;
    cin >> pid;

    cout << "Enter Doctor ID: ";
    int did;
    cin >> did;

    // Check if patient exists
    bool patientFound = false;
    for (auto& p : patients) {
        if (p.getPatientID() == pid) {
            patientFound = true;

            // Check if doctor exists
            bool doctorFound = false;
            for (const auto& d : doctors) {
                if (d.getDoctorID() == did) {
                    doctorFound = true;
                    break;
                }
            }

            if (!doctorFound) {
                cout << "\nError: Doctor ID does not exist!\n";
                return;
            }

            p.setAssignmentDoctorID(did);
            savePatientsToFile("patients.txt");
            cout << "\nDoctor assigned successfully!\n";
            return;
        }
    }

    if (!patientFound) cout << "\nError: Patient ID does not exist!\n";
}

// ------------------- APPOINTMENT FUNCTIONS -------------------

void HospitalManagement::createAppointment() {
    cout << "\nEnter Doctor ID: ";
    int did;
    cin >> did;

    cout << "Enter Patient ID: ";
    int pid;
    cin >> pid;

    // Validate both IDs
    bool doctorExists = false, patientExists = false;

    for (auto& d : doctors)
        if (d.getDoctorID() == did) doctorExists = true;

    for (auto& p : patients)
        if (p.getPatientID() == pid) patientExists = true;

    if (!doctorExists || !patientExists) {
        cout << "\nError: Invalid doctor or patient ID!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Appointment Date and Time: ";
    string datetime;
    getline(cin, datetime);

    Appointment a(nextAppointmentID, did, pid, datetime);
    appointments.push_back(a);
    nextAppointmentID++;

    saveAppointmentsToFile("appointments.txt");
    cout << "\nAppointment created successfully!\n";
}

void HospitalManagement::listAppointments() const {
    if (appointments.empty()) {
        cout << "\nNo appointments found.\n";
        return;
    }
    for (const auto& a : appointments)
        a.displayAppointment();
}

// ------------------- FILE HANDLING -------------------

void HospitalManagement::saveDoctorsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& d : doctors) {
        file << d.toFileString() << "\n";
    }
}

void HospitalManagement::loadDoctorsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Doctor d;
        d.fromFileString(line);
        doctors.push_back(d);
    }
}

void HospitalManagement::savePatientsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& p : patients) {
        file << p.toFileString() << "\n";
    }
}

void HospitalManagement::loadPatientsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Patient p;
        p.fromFileString(line);
        patients.push_back(p);
    }
}

void HospitalManagement::saveAppointmentsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& a : appointments) {
        file << a.toFileString() << "\n";
    }
}

void HospitalManagement::loadAppointmentsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Appointment a;
        a.fromFileString(line);
        appointments.push_back(a);
    }
}

// ------------------- MENUS -------------------

void HospitalManagement::manageDoctors() {
    int choice;
    do {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. Add Doctor\n";
        cout << "2. List Doctors\n";
        cout << "3. Search Doctor\n";
        cout << "4. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: listDoctors(); break;
            case 3: searchDoctorByID(); break;
        }
    } while (choice != 4);
}

void HospitalManagement::managePatients() {
    int choice;
    do {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. List Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Assign Doctor\n";
        cout << "5. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: listPatients(); break;
            case 3: searchPatientByID(); break;
            case 4: assignDoctorToPatient(); break;
        }
    } while (choice != 5);
}

void HospitalManagement::manageAppointments() {
    int choice;
    do {
        cout << "\n--- Appointment Menu ---\n";
        cout << "1. Create Appointment\n";
        cout << "2. List Appointments\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAppointment(); break;
            case 2: listAppointments(); break;
        }
    } while (choice != 3);
}

void HospitalManagement::mainMenu() {
    int choice;
    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Doctors\n";
        cout << "2. Patients\n";
        cout << "3. Appointments\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manageDoctors(); break;
            case 2: managePatients(); break;
            case 3: manageAppointments(); break;
            case 4: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid choice!\n";
        }

    } while (choice != 4);
}
